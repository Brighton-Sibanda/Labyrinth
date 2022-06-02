#include "view.hxx"


int grid_size = 60;


View::View(Model const& model)
        : model_(model),
        gen_sprite({grid_size, grid_size}, {46, 0,0})
{}

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    for (int i = 0; i < 9; i++){
        for (int j =0; j<12;j++){
            set.add_sprite(gen_sprite, {j * grid_size, i * grid_size});
        }
    }
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

