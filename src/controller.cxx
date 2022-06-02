#include "controller.hxx"

Controller::Controller(Model::vector_of_doors door,
                       Model::vector all,
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
    view_.draw(set);
}

void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int>)
{

    model_.start_game();
}

void
Controller::on_frame(double dt){
    model_.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const {
    return view_.initial_window_dimensions();
}

