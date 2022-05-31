#include "model.hxx"



Model::Model(Rectangle all,
             vector coins,
             vector shooters,
             vector spikes,
             vector treasures,
             std::vector<int> trophy,
             vector wall,
             Position door, vector arrow)
        :coins(coins),
         treasure(treasures),
         spikes_(spikes),
         all_positions_(all),
         trophy_(trophy),
         shooter_(shooters),
         player_(),
         wall_(wall),
         door_pos(door),
         time(300),
         arrows_(arrow)

{

}

Model::Position
Model::vec_to_pos(std::vector<int> vec){
    return Position {vec[0], vec[1]};
}

void
Model::start_game(){
    is_game_over = false;
}



Player
Model::get_player(){
    return player_;
}



std::vector<Game_element>
Model::get_elements(Position pos){
    std::vector<Game_element> elements;
    for (Position poss: arrows_){
        if (pos == poss){
            char name[6];
            strcpy(name, "arrow");
            elements.push_back(Game_element(true, name, pos_to_vec(pos),-5,
                                            pos_to_vec(Position {10, 10}) ));
        }
    }
    for (Position poss: spikes_){
        if (pos == poss){
            char name[6];
            strcpy(name, "spike");
            elements.push_back(Game_element(true,name , pos_to_vec(pos),-25,
                                            pos_to_vec(Position {0, 0})));
        }
    }
    for (Position poss: coins){
        if (pos == poss){
            char name[5];
            strcpy(name, "coin");
            elements.push_back(Game_element(true, name, pos_to_vec(pos),10,
                                            pos_to_vec(Position {0, 0}) ));
        }
    }
    for (Position poss: treasure){
        if (pos == poss){
            char name[9];
            strcpy(name, "treasure");
            elements.push_back(Game_element(true, name,
                                            pos_to_vec(pos),100,{0, 0}));
        }
    }

    return elements;
}

std::vector<Model::Position>
Model::get_shooters(){
    return shooter_;
}

std::vector<Model::Position>
Model::get_spikes()
{
    return spikes_;
}

void
Model::apply_elements(Position pos){
    std::vector<Game_element> elements = Model::get_elements(pos);
    for (Game_element element: elements){
        int index = Model::get_element_index(elements, element);
        if (strcmp (element.type, "coin") ==0){
            coins.erase(coins.begin() + index);
            player_.set_score(10);
        }
        else if (strcmp (element.type, "treasure") ==0){
            treasure.erase(treasure.begin() + index);
            player_.set_score(100);}
        else if (strcmp (element.type, "arrow") ==0){
            arrows_.erase(arrows_.begin() + index);
            player_.set_score(-10);
            player_.reduce_health();
        }
        else if (strcmp (element.type, "spike") ==0){
            spikes_.erase(spikes_.begin() + index);
            player_.set_score(-25);
            player_.reduce_health();
            //player_.set_pos(0,20);
        }

    }
}


int
Model::get_element_index(std::vector<Game_element> elements, Game_element
element){
    int i = 0;
    for (Game_element elemento : elements){
        if (elemento.points == element.points){
            return i;
        }
        i++;
    }
    return i;
}

Model::Position
Model::get_door_pos(){
    return door_pos;
}

void
Model::set_spikes(std::vector<Position> vec){
     spikes_ = vec;
}

void
Model::set_door_pos(Model::Position pos){
    door_pos = pos;
}


void
Model::set_coins(std::vector<Model::Position> vec){
    coins = vec;
}

void
Model::set_treasure(std::vector<Position> vec)
{
    treasure = vec;
}

void
Model::set_shooter(std::vector<Position> vec){
     shooter_ = vec;
}

void
Model::set_wall(std::vector<Position> vec){
     wall_ = vec;
}

std::vector<int>
Model::pos_to_vec(Position pos){
    std::vector<int> poss;
    poss[0] = pos.x;
    poss[1] = pos.y;
    return poss;
}

void
Model::set_game_over(){
    is_game_over = true;
    player_.set_score(time);
}

bool
Model::player_against_wall(Position pos){
   for (Position poss: wall_){
       if (poss == pos){
           return true;
       }
   }
   return false;
}

bool
Model::move(Dimensions dir){

    Position current = vec_to_pos(player_.get_position());
    Position next = {current.x + dir.x, current.y +dir.y};

    float player_score = player_.get_score();
    apply_elements(next);
    if (player_score - 25 == player_.get_score()){
        player_.set_pos(0,20);
        player_.set_velocity({0,0});
        player_.set_acceleration(1);
        }
    else {
        player_.set_pos(next.x, next.y);
        player_.set_acceleration(1);
        int x = player_.get_velocity()[0] + dir.x * player_
                .get_acceleration();
        int y = player_.get_velocity()[1] + dir.y * player_
                .get_acceleration();
        player_.set_velocity({x,y});
        }

    return true;
}

void
Model::on_frame(float dt){
    time -= dt;
    if (player_.get_health()==0){
        set_game_over();
    }
}