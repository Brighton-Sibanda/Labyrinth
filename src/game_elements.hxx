#include <stdio.h>
#include<vector>
using namespace std;

class Game_element{
public:

    Game_element(bool, char*, std::vector<int>, int, std::vector<int>);

    bool active;
    char* type;
    std::vector<int> pos;
    int points;
    std::vector<int> velocity;

};