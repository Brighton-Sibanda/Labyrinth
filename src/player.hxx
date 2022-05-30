//
// Created by Brighton Sibanda on 5/30/22.
//

#ifndef GAME_PLAYER_HXX
#define GAME_PLAYER_HXX

#include <stdio.h>
#include<vector>

using namespace std;

class Player
{
public:
    Player(); //constructor
    // health,
    // velocity, current pos, score, acc
    std::vector<int> get_position();
    int get_health();
    float get_score();
    std::vector<int> get_velocity();
    float get_acceleration();
    void reduce_health();
    void set_score(float change);
    void set_acceleration(float change);
    void set_pos(int, int);

private:
    std::vector<int> current_pos;
    int health;
    float score;
    std::vector<int> velocity;
    float acceleration;
};


#endif //GAME_PLAYER_HXX
