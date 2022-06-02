#include "view.hxx"


int grid_size = 60;


View::View(Model const& model)
        : model_(model),
        gen_sprite({grid_size, grid_size},
                   {255, 0,0}),
        player_sprite({grid_size, grid_size * 2},
                      {200, 100,120})
{ }

void
View::draw(ge211::Sprite_set& set) {
    for (Model::Position pos: model_.get_all() ){
        set.add_sprite(gen_sprite, {pos.x, pos.y});
    }
    set.add_sprite(player_sprite,
                   model_.vec_to_pos(model_.get_player().get_position()));
}

std::string
View::initial_window_title() const
{
    return "Labyrinth";
}

ge211::Dims<int>
View::initial_window_dimensions() const{
    return ge211::Dims<int> {12 * grid_size,9 * grid_size};
}

ge211::Posn<int>
View::screen_to_board(ge211::Posn<int> pos) const {
    return {pos.x / grid_size, pos.y / grid_size};
}

ge211::Posn<int>
View::board_to_screen(ge211::Posn<int> pos) const {
    return {pos.x * grid_size, pos.y * grid_size};
}

