#include "view.hxx"

int grid_size = 60;



View::View(Model const& model)
        : model_(model),
        gen_sprite({grid_size, grid_size}, {46, 0,0}),
        player_sprite({grid_size/2, grid_size}, {200, 100,120}),
        wall_sprite({grid_size, grid_size}, {50,0 ,50}),
        door_sprite({grid_size/2, grid_size}, {100, 100,100}),
        spike_sprite({grid_size, grid_size/2}, {255, 255,0}),
        treasure_sprite({grid_size/3, grid_size/3}, {148, 0,211}),
        trophy_sprite({grid_size/2, grid_size}, {200, 100,120}),
        arrow_sprite({grid_size/4, grid_size/4}, {255, 0,0}),
        coin_sprite(grid_size/6, {100, 70,0})

{ }

void
View::draw(ge211::Sprite_set& set) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 12; j++) {
            set.add_sprite(gen_sprite, {j * grid_size, i * grid_size}, 0);
        }
    }
    set.add_sprite(player_sprite,
                   board_to_screen(model_.vec_to_pos(model_.get_player()
                   .get_position())), 10);
    for (Model::Position pos: model_.get_wall()){
        set.add_sprite(wall_sprite, board_to_screen(pos), 2);
    }
    for (Door door: model_.get_doors()){
        set.add_sprite(door_sprite, board_to_screen(model_.vec_to_pos(door
        .door_pos)), 3);
    }
    for (Model::Position pos: model_.get_coins()){
        set.add_sprite(coin_sprite, board_to_screen(pos), 2);
    }

    for (Model::Position pos: model_.get_spikes()){
        set.add_sprite(spike_sprite, board_to_screen(pos), 1);
    }
    for (Model::Position pos: model_.get_treasure()){
        set.add_sprite(treasure_sprite, board_to_screen(pos), 4);
    }
    for (Shooter shooterr: model_.get_shooters()){
        for (Model::Position pos: shooterr.arrows){
            set.add_sprite(arrow_sprite, board_to_screen(pos), 7);
        }
    }



}

std::string
View::initial_window_title() const {
    return "Labyrinth";
}

ge211::Dims<int>
View::initial_window_dimensions() const {
    return ge211::Dims<int> {12 * grid_size, 9 * grid_size};
}

ge211::Posn<int>
View::screen_to_board(ge211::Posn<int> posn) const {
    return {posn.x / grid_size, posn.y / grid_size};
}

ge211::Posn<int>
View::board_to_screen(ge211::Posn<int> posn) const {
    return { grid_size * posn.x , grid_size *posn.y };
}