#include "view.hxx"


int grid_size = 36;


View::View(Model const& model)
        : model_(model),
        gen_sprite({grid_size, grid_size}, {255, 0,0})
{ }

void
View::draw(ge211::Sprite_set& set)
{
    for (Model::Position pos: model_.get_all() ){
        set.add_sprite(gen_sprite, {pos.x * grid_size, pos.y * grid_size});
    }
    set.add_sprite(gen_sprite, {1 * grid_size, 1 * grid_size});
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

