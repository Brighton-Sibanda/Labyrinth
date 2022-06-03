//
// Created by Brighton Sibanda on 5/30/22.
//

// #ifndef GAME_PLAYER_HXX
// #define GAME_PLAYER_HXX

#include <stdio.h>
#include <vector>

using namespace std;

class Player
{
public:
    Player(); //constructor
    // health, velocity, current pos, score, acc

    // Get functions for private members
    std::vector<int> get_position();
    int get_health();
    float get_score();
    std::vector<int> get_velocity();
    std::vector<int> get_acceleration();
    bool get_jump();

    // Set functions for private members
    void set_pos(int x, int y);
    void set_health(int h);
    void set_score(float change);
    void set_acceleration(std::vector<int> acc);
    void set_velocity(std::vector<int> vel);
    void set_jump(bool jump);

    // State functions
    void reduce_health();
    void accelerate();

private:
    std::vector<int> current_pos;
    int health;
    float score;
    std::vector<int> velocity;
    std::vector<int> acceleration;
    bool jump;
};


// #endif //GAME_PLAYER_HXX
