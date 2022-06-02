#include "controller.hxx"

Controller::Controller(Model::vector_of_doors door,
                       Model::vector coin,
                       std::vector<Shooter> shooter,
                       Model::vector spike,
                       Model::vector treasure,
                       Model::Position trophy,
                       Model::vector wall,
                       Model::vector arrow)
        : model_(door, coin, shooter, spike, treasure, trophy,wall,
                 arrow),
          view_(model_)

{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_frame(double dt){
    model_.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const {
    return view_.initial_window_dimensions();
}

void
Controller::on_key(ge211::Key key)
{
     if (key == ge211::Key::code('d')) {
         if (model_.good_position({model_.get_player().get_position()[0] + 1,
                                   model_.get_player().get_position()[1]})){
             model_.set_player_acc({1,0});
        }
     }

    if (key == ge211::Key::code('a')) {
        if (model_.good_position({model_.get_player().get_position()[0] - 1,
                                  model_.get_player().get_position()[1]}) ){
            model_.set_player_acc({-1,0});
        }
    }
    if (key == ge211::Key::code('w')) {
        if (model_.good_position({model_.get_player().get_position()[0],
                                  model_.get_player().get_position()[1] - 1}) ){
            model_.set_player_acc({0,-1});
        }
    }

    if (key == ge211::Key::code('s')) {
        if (model_.good_position({model_.get_player().get_position()[0],
                                  model_.get_player().get_position()[1]+1})){
            model_.set_player_acc({0,1});
        }
    }

    model_.move();
}

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::code('d')) {
        model_.set_player_acc({0,0});
    }

    if (key == ge211::Key::code('a')) {
        model_.set_player_acc({0,0});

    }
    if (key == ge211::Key::code('w')) {
        model_.set_player_acc({0,0});
    }

    if (key == ge211::Key::code('s')) {
        model_.set_player_acc({0,0});
    }
}