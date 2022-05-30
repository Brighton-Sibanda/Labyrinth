#include "model.hxx"
#include "player.hxx"

// struct Player{
//     int h;
//     Model::Position v;
//     Model::Position pos;
//     int a;
//     int s;
//
// };


Model::Model(Rectangle all,
             vector coins,
             vector shooters,
             vector spikes,
             vector treasures,
             std::vector<int> trophy,
             vector wall,
             Position door)
        :coins(coins),
         treasure(treasures),
         spikes_(spikes),
         all_positions_(all),
         trophy_(trophy),
         shooter_(shooters),
         player_(),
         wall_(wall),
         door_pos(door),
         time(300)

{

}

bool pos_comp (Model::Position pos, std::vector<int> pos2){
    return pos2[0] == pos.x && pos.y == pos2[1];
}

void
Model::start_game(){
    is_game_over = false;
}

Player
Model::get_player(){
    return player_;
}

bool

Model::safe_position(Position pos){

     return true;

}

