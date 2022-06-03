#include "model.hxx"



Model::Model(vector_of_doors door,
             vector coins,
             std::vector<Shooter> shooters,
             vector spikes,
             vector treasures,
             Position trophy,
             vector wall,
             vector arrow)
        :doors(door),
         coins(coins),
         treasure(treasures),
         spikes_(spikes),
         trophy_(trophy),
         shooter_(shooters),
         player_(),
         wall_(wall),
         time_for_points(300),
         arrows_(arrow)
{
}

Shooter::Shooter(char type,ge211::Posn<int> pos,
                 std::vector<ge211::Posn<int>> arrows)
        :type(type),
         Pos(pos),
         arrows(arrows)
{}



// Especially for the player velocity
Model::Position
Model::vec_to_pos(std::vector<int> vec) const {
    return Position {vec[0], vec[1]};
}

std::vector<int>
Model::pos_to_vec(Position pos){
    std::vector<int> poss = {pos.x, pos.y};
    return poss;
}

// void
// Model::start_game(){
//     is_game_over = false;
// }


Player
Model::get_player() const {
    return player_;
}



std::vector<Game_element>
Model::get_elements(Position pos){
    std::vector<Game_element> elements;
    // If there is an arrow in a given position
    for (Position poss : arrows_){
        if (pos == poss){
            elements.push_back(Game_element(true, 'a', pos_to_vec(pos), -5));
        }
    }
    // If there are spikes in a given position
    for (Position poss: spikes_){
        if (pos == poss){
            elements.push_back(Game_element(true,'s' , pos_to_vec(pos),-25));
        }
    }
    // If there is a coin in a given position
    for (Position poss: coins){
        if (pos == poss){
            elements.push_back(Game_element(true, 'c', pos_to_vec(pos),10));
        }
    }
    // If there is a treasure chest in a given position
    for (Position poss: treasure){
        if (pos == poss){
            elements.push_back(Game_element(true, 't',pos_to_vec(pos),100));
        }
    }

    return elements;
}

std::vector<Shooter>
Model::get_shooters() const {
    return shooter_;
}

std::vector<Model::Position>
Model::get_spikes() const {
    return spikes_;
}


void
Model::apply_elements(Position pos){
    std::vector<Game_element> elements = Model::get_elements(pos);
    for (Game_element element: elements){
        if (element.type == 'c'){
            int index = Model::get_element_index(coins, pos);
            coins.erase(coins.begin() + index);
            player_.set_score(10);
        }
        else if (element.type=='t'){
            int index = Model::get_element_index(treasure, pos);
            treasure.erase(treasure.begin() + index);
            player_.set_score(100);
        }
        else if (element.type== 'a'){
            int index = Model::get_element_index(arrows_, pos);
            arrows_.erase(arrows_.begin() + index);
            player_.set_score(-10);
            player_.reduce_health();
            // Respawn
            player_.set_pos(1, 8);
            player_.set_velocity({0,0});
            player_.set_acceleration({0,0});

        }
        else if (element.type == 's'){
            player_.set_score(-25);
            player_.reduce_health();
            // Respawn
            player_.set_pos(1, 8);
            player_.set_velocity({0,0});
            player_.set_acceleration({0,0});
        }
    }
}


int
Model::get_element_index(std::vector<Position> elements, Position pos){
    int i = 0;
    for (Position elemento : elements){
        if (pos == elemento){
            return i;
        }
        i++;
    }
    return i;
}


Model::vector_of_doors
Model::get_doors() const{
    return doors;
}


void
Model::set_spikes(std::vector<Position> vec) {
    spikes_ = vec;
}

void
Model::set_doors(Model::vector_of_doors doorss) {
    doors = doorss;
}



void
Model::set_coins(std::vector<Model::Position> vec) {
    coins = vec;
}

void
Model::set_treasure(std::vector<Position> vec) {
    treasure = vec;
}

void
Model::set_shooter(std::vector<Shooter> vec) {
    shooter_ = vec;
}

void
Model::set_wall(std::vector<Position> vec) {
    wall_ = vec;
}

void
Model::set_game_over() {
    is_game_over = true;
    if (time_for_points > 0){
    player_.set_score(time_for_points);}
}

///////////////////////
bool
Model::player_against_wall(Position pos){
    for (Position poss : wall_){
        if (poss == pos){
            return true;
        }
    }
    return false;
}
///////////////////////

bool
Model::move(){

    // Checks if the game is over
    if (player_.get_health() == 0 || is_game_over){
        set_game_over();
        return false;
    }

    // Player overlaps with an obstacle
    if (!good_position(vec_to_pos(player_.get_position())) || is_game_over){
        player_.set_velocity({0,0});
        return true;
    }

    int health = player_.get_health();
    Position current = vec_to_pos(player_.get_position());
    Position next = {current.x + player_.get_velocity()[0],
                     current.y + player_.get_velocity()[1]};

    // applies all elements in the position the player is moving into
    apply_elements(next);

    if (player_.get_health() < health){
        return true;
    }

    // Sets player's new position and velocity
    if (good_position(next)){
        player_.set_pos(next.x, next.y);
        int x = player_.get_velocity()[0] + player_.get_acceleration()[0];
        int y = player_.get_velocity()[1] + player_.get_acceleration()[1];
        player_.set_velocity({x, y});}

    // If the trophy is reached
    if (player_.get_position() == pos_to_vec(trophy_)) {
        set_game_over();
        return true;
    }

    // Changes room/grid if the player reaches a door
    for (Door door: doors){
        if (door.door_pos == player_.get_position()){
            if (door.changes_model_state){
                change_to_stage_1();
                player_.set_pos(door.destination[0], door.destination[1]);
                model_state = 1;
            }
            else{
                player_.set_pos(door.destination[0], door.destination[1]);
            }
        }
    }

    return false;
}

void
Model::on_frame(float dt)
{
    if (is_game_over) {
        return;
    }
    apply_elements(vec_to_pos(player_.get_position()));
    time_for_points -= 1;
    time_total += 1;
    shoot();

}
void
Model::change_to_stage_1() {

}

//main shoot function
void
Model::shoot(){
    for (Shooter shooterr : shooter_){
        if (shooterr.type == 'u'){
            shoot_up(shooterr);
        }
        else if (shooterr.type == 'd'){
            shoot_down(shooterr);
        }
        else if (shooterr.type == 'l'){
            shoot_left(shooterr);
        }
        else if (shooterr.type == 'r'){
            shoot_right(shooterr);
        }
    }
}

//Helper functions for shoot
void
Model::shoot_up(Shooter shooterr){
    Position pos = shooterr.Pos;
    std::vector<Game_element> elements;
    if (time_total % 200 == 0){
        for (int i = pos.y; i>=0;i--){
            std::vector<Game_element> elementos = get_elements({pos.x, i});
            for (Game_element elemento: elementos){
                elements.push_back(elemento);

            }
        }
        for (Game_element elemento: elements){
            if (elemento.type == 'a' && good_position(vec_to_pos(elemento.pos))){
                arrows_.push_back({elemento.pos[0], elemento.pos[1]-1});
                arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                                  vec_to_pos
                                                                          (elemento
                                                                                   .pos)));
            }}

        }
    if (time_total % 600 == 0){
        arrows_.push_back({shooterr.Pos.x, shooterr.Pos.y -1});
    }
}

void
Model::shoot_down(Shooter shooterr){
    Position pos = shooterr.Pos;
    std::vector<Game_element> elements;
    if (time_total % 200 == 0) {
        for (int i = pos.y; i < 12; i++) {
            std::vector<Game_element> elementos = get_elements({pos.x, i});
            for (Game_element elemento: elementos) {
                elements.push_back(elemento);

            }
        }
        for (Game_element elemento: elements) {
            if (elemento.type == 'a' &&
                good_position(vec_to_pos(elemento.pos))) {
                arrows_.push_back({elemento.pos[0], elemento.pos[1] + 1});
                arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                                  vec_to_pos
                                                                          (elemento
                                                                                   .pos)));
            }
        }
    }
        if (time_total % 600 ==0 ){
            arrows_.push_back({shooterr.Pos.x + 1, shooterr.Pos.y});}
}
void
Model::shoot_left(Shooter shooterr){
    Position pos = shooterr.Pos;
    std::vector<Game_element> elements;
    if (time_total % 200 == 0) {
        for (int i = pos.x; i >= 0; i--) {
            std::vector<Game_element> elementos = get_elements({i, pos.y});
            for (Game_element elemento: elementos) {
                elements.push_back(elemento);

            }
        }
        for (Game_element elemento: elements) {
            if (elemento.type == 'a' &&
                good_position(vec_to_pos(elemento.pos))) {
                arrows_.push_back({elemento.pos[0] - 1, elemento.pos[1]});
                arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                                  vec_to_pos
                                                                          (elemento
                                                                                   .pos)));
            }
        }
    }
    if (time_total % 600 == 0){
        arrows_.push_back({shooterr.Pos.x + 1, shooterr.Pos.y});}
}

void
Model::shoot_right(Shooter shooterr){

    Position pos = shooterr.Pos;
    std::vector<Game_element> elements;
    if (time_total % 200 == 0) {
        for (int i = pos.x; i < 12; i++) {
            std::vector<Game_element> elementos = get_elements({i, pos.y});
            for (Game_element elemento: elementos) {
                elements.push_back(elemento);

            }
        }
        for (Game_element elemento: elements) {
            if (elemento.type == 'a' &&
                good_position(vec_to_pos(elemento.pos))) {
                arrows_.push_back({elemento.pos[0] + 1, elemento.pos[1]});
                arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                                  vec_to_pos
                                                                          (elemento
                                                                                   .pos)));
            }
        }
    }
    if(time_total % 400 == 0){
    arrows_.push_back({shooterr.Pos.x + 1, shooterr.Pos.y});}

}


Model::vector
Model::get_wall() const{
    return wall_;
}

Model::vector
Model::get_coins() const{
    return coins;
}

Model::vector
Model::get_treasure() const{
    return treasure;
}


bool
Model::good_position(Position pos){
    bool grids = 0 <= pos.x && pos.x < 12 &&
                 0 <= pos.y && pos.y < 9;
    bool wall = true;
    for (Position poss: wall_){
        if (pos == poss){
            wall = false;
        }
    }
    return grids && wall;
}

void
Model::set_player_acc(std::vector<int> acc){
    player_.set_velocity(acc);
}

void
Model::set_player_pos(std::vector<int> pos){
    player_.set_pos(pos[0], pos[1]);
}

Model::vector
Model::get_arrows() const{
    return arrows_;
}
void
Model::set_arrows(vector arrow){
    arrows_ = arrow;
}