#include "controller.hxx"
#include "model.hxx"
#include <ge211.hxx>

int
main()
{
    Controller(Model::vector_of_doors {{true, {2,1}, {1,8}}},
               Model::Rectangle {0,0,12,9},     // all
               Model::vector {{4,7},{5,7},{6,7},{7,7}
               ,{8,7},{4,8},{5,8},{6,8},{7,8},{8,8}
                       ,{10,3},{11,3},{10,4},{11,4},{10,5}
                       ,{11,5},{10,6},
                       {11,6}},        // coin
               std::vector<Shooter> {{'r', {0,2},{}}},         // shooter
               Model::vector {},        // spike
               Model::vector {},        // treasure
               Model::Position {3,4},  //trophy
               Model::vector{},         // wall
               Model::vector {}).run();       // arrow
    return 0;
}
