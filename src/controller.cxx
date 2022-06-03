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
Controller::on_key(ge211::Key key) {

    // Storing player velocity and acceleration
    std::vector<int> vel = model_.get_player().get_velocity();
    std::vector<int> acc = model_.get_player().get_acceleration();

    // Projecting next position for calculations
    Model::Position next = {model_.get_player().get_position()[0] +
                            model_.get_player().get_velocity()[0],
                            model_.get_player().get_position()[1] +
                            model_.get_player().get_velocity()[1],};

    // Right: acceleration is positive if next is a good position
    // Player stops moving otherwise
     if (key == ge211::Key::code('d')) {
         if (model_.good_position(next)){
             model_.set_player_acc({1, acc[1]});
        }
         else {
             model_.set_player_acc({0, acc[1]});
             model_.set_player_vel({0, acc[1]});
         }
     }

    // Left: acceleration is positive if next is a good position
    // Player stops moving otherwise
    if (key == ge211::Key::code('a')) {
        if (model_.good_position(next)){
            model_.set_player_acc({-1, acc[1]});
        }
        else {
            model_.set_player_acc({0, acc[1]});
            model_.set_player_vel({0, acc[1]});

        }
    }
    if (key == ge211::Key::code('w')) {
        if (model_.good_position(next)) {
            model_.set_player_vel({0, 5});
            model_.set_player_acc({0, -1});
        }
    }
    // if (key == ge211::Key::code('s')) {
    //     if (model_.good_position(next)){
    //         model_.set_player_acc({0,-1});
    //     }
    // }

    model_.move();
}

void
Controller::on_key_up(ge211::Key key)
{
    std::vector<int> vel = model_.get_player().get_velocity();
    std::vector<int> acc = model_.get_player().get_acceleration();
    Model::Position next = {model_.get_player().get_position()[0] +
                             model_.get_player().get_velocity()[0],
                             model_.get_player().get_position()[1] +
                             model_.get_player().get_velocity()[1],};

    if (key == ge211::Key::code('d')) {
        if (vel[0] < 0 && model_.good_position(next)) {
            model_.set_player_acc({-1, acc[1]});
        }
        else {
            model_.set_player_acc({0, acc[1]});
            model_.set_player_vel({0, acc[1]});
        }
    }

    if (key == ge211::Key::code('a')) {
        if (vel[0] > 0 && model_.good_position(next)) {
            model_.set_player_acc({-1, acc[1]});
        }
        else {
            model_.set_player_acc({0, acc[1]});
            model_.set_player_vel({0, acc[1]});
        }
    }
    if (key == ge211::Key::code('w')) {
        if (vel[1] > 0 && model_.good_position(next)) {
            model_.set_player_acc({acc[0], -1});
        }
        else {
            model_.set_player_acc({acc[0], 0});
            model_.set_player_vel({acc[0], 0});
        }
    }

    // if (key == ge211::Key::code('s')) {
    //     model_.set_player_acc({0,0});
    // }
}