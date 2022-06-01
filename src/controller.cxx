#include "controller.hxx"

Controller::Controller(Model::vector_of_doors door,
                       Model::Rectangle all,
                       Model::vector coin,
                       std::vector<Shooter> shooter,
                       Model::vector spike,
                       Model::vector treasure,
                       Model::Position trophy,
                       Model::vector wall,
                       Model::vector arrow)
        : model_(door,all, coin, shooter, spike, treasure, trophy,wall,
                 arrow),
          view_(model_)

{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, );
}


