#include <stdio.h>
#include<vector>

using namespace std;

class Game_element{
public:
    //constructor for a game element
    Game_element(bool, char, std::vector<int>, int, std::vector<int>);


    //attributes of a game element
    bool active;
    char type;
    std::vector<int> pos;
    int points;
    //char orientation;
    std::vector<int> velocity;

};