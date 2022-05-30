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

private:
    std::vector<int> current_pos;
    int health;
    int score;
    std::vector<int> velocity;
    float acceleration;
};


#endif //GAME_PLAYER_HXX
