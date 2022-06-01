#include "view.hxx"


int grid_size = 36;


View::View(Model const& model)
        : model_(model),
        gen_sprite({grid_size, grid_size}, {255, 0,0})
{ }

void
View::draw(ge211::Sprite_set& set)
{
    // This needs to do something!
    for (Model::Position pos: model_.get_all() ){
        set.add_sprite(gen_sprite, {pos.x * grid_size, pos.y * grid_size});
    }

}
