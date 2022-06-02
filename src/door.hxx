#include <stdio.h>
#include <vector>
using namespace std;

class Door{
public:
    Door(bool,std::vector<int>, std::vector<int>);
    std::vector<int> door_pos;
    std::vector<int> destination;
    bool changes_model_state;

};