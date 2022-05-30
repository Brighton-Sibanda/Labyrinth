#pragma once

#include <ge211.hxx>
#include "player.hxx"


class Model
{

public:
    using Position = ge211::Posn<int>;
    using vector = std::vector<Position>;
    using Rectangle = ge211::Rect<int>;

    Model(Rectangle all, vector co, vector sh,
                   vector sp,
                   vector tr, std::vector<int> trophy, vector wall, Position
                   door_pos);

    vector coins;
    vector treasure;

    bool pos_comp (Model::Position, std::vector<int>); //compares positions
    // to vectors
    void start_game();
    Player get_player();
    bool safe_position(Position pos);





private:
    //char board_[3][3];
    //char winner_;
    //int score;

    vector spikes_;
    Rectangle all_positions_;
    std::vector<int> trophy_;
    vector shooter_;
    Player player_;
    bool is_game_over = true;
    vector wall_;
    Position door_pos;
    float time;

};
