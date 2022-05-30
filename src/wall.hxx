#include <stdio.h>
#include <vector>
using namespace std;

class Wall {
public:

    Wall(char*, vector<int>);

    // can be surface, shooter, or door
    char* type;
    vector<int> position;

};