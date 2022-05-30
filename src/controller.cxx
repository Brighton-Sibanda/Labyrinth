#include "controller.hxx"

Controller::Controller(Model::Rectangle all, Model::vector co,
                       Model::vector sh,Model::vector sp,Model::vector tr,
                       std::vector<int> trophy, Model::vector wall,
                       Model::Position door)
        : model_(all, co, sh, sp, tr, trophy,wall, door),
          view_(model_)

{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}


