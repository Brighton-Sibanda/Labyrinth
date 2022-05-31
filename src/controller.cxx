#include "controller.hxx"

Controller::Controller(Model::Rectangle all,
                       Model::vector coin,
                       Model::vector shooter,
                       Model::vector spike,
                       Model::vector treasure,
                       std::vector<int> trophy,
                       Model::vector wall,
                       Model::vector door,
                       Model::vector arrow)
        : model_(all, coin, shooter, spike, treasure, trophy,wall, door, arrow),
          view_(model_)

{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}


