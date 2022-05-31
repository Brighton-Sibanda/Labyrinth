#include "controller.hxx"
#include "model.hxx"
#include <ge211.hxx>

int
main()
{
    Controller(Model::Rectangle {},     // all
               Model::vector {},        // coin
               Model::vector {},         // shooter
               Model::vector {},        // spike
               Model::vector {},        // treasure
               Model::Position {0,0},  //trophy
               Model::vector{},         // wall
               Model::Position {0,0},   // door_pos
               Model::vector {}).run();       // arrow
    return 0;
}
