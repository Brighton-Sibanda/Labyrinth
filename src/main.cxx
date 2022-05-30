#include "controller.hxx"
#include "model.hxx"
#include <ge211.hxx>

int
main()
{
    Controller(Model::Rectangle {}, Model::vector
    {},Model::vector{},Model::vector {},Model::vector {}, std::vector<int>
            {0,0}, Model::vector{}, Model::Position {0,0}).run();
    return 0;
}
