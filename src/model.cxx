#include "model.hxx"



Model::Model(vector_of_doors door,
             vector all,
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
         all_positions_(all),
         trophy_(trophy),
         shooter_(shooters),
         player_(),
         wall_(wall),
         time_for_points(300),
         arrows_(arrow)
{
    time_total =0;
}

Shooter::Shooter(char type,ge211::Posn<int> pos,
                 std::vector<ge211::Posn<int>> arrows)
        :type(type),
         Pos(pos),
         arrows(arrows)
{}



// Especially for the player velocity
Model::Position
Model::vec_to_pos(std::vector<int> vec) {
    return Position {vec[0], vec[1]};
}

std::vector<int>
Model::pos_to_vec(Position pos){
    std::vector<int> poss;
    poss[0] = pos.x;
    poss[1] = pos.y;
    return poss;
}

void
Model::start_game(){
    is_game_over = false;
}


Player
Model::get_player() const{
    return player_;
}


std::vector<Game_element>
Model::get_elements(Position pos){
    std::vector<Game_element> elements;
    // If there is an arrow in a given position
    for (Position poss : arrows_){
        if (pos == poss){
            elements.push_back(Game_element(true, 'a', pos_to_vec(pos), -5,
                                            {10, 10} ));
        }
    }
    // If there are spikes in a given position
    for (Position poss: spikes_){
        if (pos == poss){
            elements.push_back(Game_element(true,'s' , pos_to_vec(pos),-25,
                                            {0, 0}));
        }
    }
    // If there is a coin in a given position
    for (Position poss: coins){
        if (pos == poss){
            elements.push_back(Game_element(true, 'c', pos_to_vec(pos),10,
                                            {0, 0} ));
        }
    }
    // If there is a treasure chest in a given position
    for (Position poss: treasure){
        if (pos == poss){
            elements.push_back(Game_element(true, 't',
                                            pos_to_vec(pos),100,{0, 0}));
        }
    }

    return elements;
}

std::vector<Shooter>
Model::get_shooters() {
    return shooter_;
}

std::vector<Model::Position>
Model::get_spikes() {
    return spikes_;
}

Model::vector
Model::get_all() const
{
    return all_positions_;
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
Model::get_doors() {
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
    player_.set_score(time_for_points);
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
Model::move(Dimensions dir){

    if (is_game_over){
        return false;
    }
    Position current = vec_to_pos(player_.get_position());
    Position next = {current.x + dir.x, current.y + dir.y};

    // applies all elements in the position the player is moving into
    apply_elements(next);
    // returns if the player got kicked to the starting position
    if(player_.get_position() == pos_to_vec({1, 8})) {
        return true;
    }
    // Sets player's new position and velocity
    player_.set_pos(next.x, next.y);
    int x = player_.get_velocity()[0] + player_.get_acceleration()[0];
    int y = player_.get_velocity()[1] + player_.get_acceleration()[1];
    player_.set_velocity({x, y});

    // If the trophy is reached
    if (player_.get_position() == pos_to_vec(trophy_)) {
        set_game_over();
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
    return true;
}

void
Model::on_frame(float dt){
    time_for_points -= dt;
    time_total += 1;
    shoot();
    if (player_.get_health()==0){
        set_game_over();
    }

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
    for (Position &pos: shooterr.arrows){
        arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                          pos));
        pos = {pos.x, pos.y - 1};
        arrows_.push_back(pos);
    }
    if (time_total % 3 == 1){

        shooterr.arrows.push_back({shooterr.Pos.x, shooterr.Pos.y
                                                   - 1});
        arrows_.push_back({shooterr.Pos.x, shooterr.Pos.y
                                           - 1});
    }
}

void
Model::shoot_down(Shooter shooterr){
    for (Position &pos: shooterr.arrows){
        arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                          pos));
        pos = {pos.x, pos.y + 1};
        arrows_.push_back(pos);
    }
    if (time_total % 3 == 1){
        shooterr.arrows.push_back({shooterr.Pos.x, shooterr.Pos.y
                                                   +1});
        arrows_.push_back({shooterr.Pos.x, shooterr.Pos.y
                                           +1});}
}
void
Model::shoot_left(Shooter shooterr){
    for (Position &pos: shooterr.arrows){
        arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                          pos));
        pos = {pos.x - 1, pos.y};
        arrows_.push_back(pos);}

    if (time_total % 3 == 1){
        shooterr.arrows.push_back({shooterr.Pos.x - 1, shooterr.Pos.y});
        arrows_.push_back({shooterr.Pos.x - 1, shooterr.Pos.y});}
}

void
Model::shoot_right(Shooter shooterr){
    for (Position &pos: shooterr.arrows){
        arrows_.erase(arrows_.begin() + get_element_index(arrows_,
                                                          pos));
        pos = {pos.x + 1, pos.y};
        arrows_.push_back(pos);
    }
    if (time_total % 3 == 1){
        shooterr.arrows.push_back({shooterr.Pos.x + 1, shooterr.Pos.y});
        arrows_.push_back({shooterr.Pos.x + 1, shooterr.Pos.y});
    }
}


