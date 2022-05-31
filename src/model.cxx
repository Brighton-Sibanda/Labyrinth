#include "model.hxx"



Model::Model(Rectangle all,
             vector coins,
             vector shooters,
             vector spikes,
             vector treasures,
             Position trophy,
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
         time_for_points(300),
         arrows_(arrow)
{
    time_total =0;
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
        if (strcmp (element.type, "coin") ==0){
            int index = Model::get_element_index(coins, pos);
            coins.erase(coins.begin() + index);
            player_.set_score(10);
        }
        else if (strcmp (element.type, "treasure") ==0){
            int index = Model::get_element_index(treasure, pos);
            treasure.erase(treasure.begin() + index);
            player_.set_score(100);}
        else if (strcmp (element.type, "arrow") ==0){
            int index = Model::get_element_index(arrows_, pos);
            arrows_.erase(arrows_.begin() + index);
            player_.set_score(-10);
            player_.reduce_health();
        }
        else if (strcmp (element.type, "spike") ==0){
            //spikes_.erase(spikes_.begin() + index);
            player_.set_score(-25);
            player_.reduce_health();
            //player_.set_pos(0,20);
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
    player_.set_score(time_for_points);
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

    if (is_game_over){
        return false;
    }
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
    if (player_.get_position() == trophy_){
        set_game_over();
    }
    if (vec_to_pos(player_.get_position()) == door_pos && model_state==0){
        Model::change_to_hidden_place();
        model_state = 1;
    }
    else if (vec_to_pos(player_.get_position()) == door_pos && model_state==1){
        Model::change_to_normal_model();
        model_state = 0;
    }
    return true;
}

void
Model::on_frame(float dt){
    time_for_points -= dt;
    time_total += 1;
    if (player_.get_health()==0){
        set_game_over();
    }

}

void
Model::change_to_hidden_place(){

}

void
Model::change_to_normal_model(){
}

void
Model::shoot(){
    if (time_total % 2 == 1){
        return;
    }
    if (arrows_.empty()){
        arrows_.push_back({shooter_[0].x + 1, shooter_[0].y});
    }
    else {
        for (Position pos: arrows_){
            Position next = {pos.x + 1, pos.y};
            arrows_.erase(arrows_.begin() + get_element_index(arrows_, pos));
            arrows_.push_back(next);
            for (Position pos_wall: wall_){
                if (pos_wall == next){
                    arrows_.pop_back();
                }
            }

        }
        arrows_.push_back({shooter_[0].x + 1, shooter_[0].y});
    }
}