#include "controller.hxx"
#include "model.hxx"
#include <ge211.hxx>

int
main()
{
    Controller(Model::vector_of_doors {},
               Model::Rectangle {},     // all
               Model::vector {},        // coin
               std::vector<Shooter> {},         // shooter
               Model::vector {},        // spike
               Model::vector {},        // treasure
               Model::Position {0,0},  //trophy
               Model::vector{},         // wall
               Model::vector {}).run();       // arrow
    return 0;
}
