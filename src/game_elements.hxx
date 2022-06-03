#include <stdio.h>
#include<vector>

using namespace std;

class Game_element{
public:
    //constructor for a game element
    Game_element(char, std::vector<int>);


    //attributes of a game element
    //bool active;
    char type;
    std::vector<int> pos;
    //int points;

};