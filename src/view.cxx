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
        arrow_sprite({grid_size/10, grid_size/10}, {255, 0,0}),
        coin_sprite(grid_size/6, {100, 70,0}),
        shooter_sprite({grid_size, grid_size}, {120, 100,30})
        // ,right_sprite("right.png"),
        // left_sprite("left.png"),
        // stationary_sprite("stationary.png")


{}

void
View::draw(ge211::Sprite_set& set) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 12; j++) {
            set.add_sprite(gen_sprite, {j * grid_size, i * grid_size}, 0);
        }
    }
    // Player Sprite
    set.add_sprite(player_sprite,
                   board_to_screen(model_.vec_to_pos(model_.get_player()
                   .get_position())),
                   10);

    for (Model::Position pos: model_.get_wall()){
        set.add_sprite(wall_sprite, board_to_screen(pos), 2);
    }
    for (Door door: model_.get_doors()){
        set.add_sprite(door_sprite, board_to_screen(model_.vec_to_pos(door
        .door_pos)), 3);
    }
    for (Model::Position pos: model_.get_coins()){
        Model::Position poss = board_to_screen({pos});
        set.add_sprite(coin_sprite, {poss.x + grid_size/4, poss.y +
        grid_size/4},2);
    }

    for (Model::Position pos: model_.get_spikes()){
        set.add_sprite(spike_sprite, board_to_screen(pos), 1);
    }
    for (Model::Position pos: model_.get_treasure()){
        set.add_sprite(treasure_sprite, board_to_screen(pos), 4);
    }
    for (Shooter shooterr: model_.get_shooters()){
        set.add_sprite(shooter_sprite, board_to_screen(shooterr.Pos), 4);

    }
    for (Model::Position pos: model_.get_arrows()){
        Model::Position poss = board_to_screen({pos});
        set.add_sprite(arrow_sprite, {poss.x + grid_size, poss.y +
        grid_size/2},7);
    }


    ge211::Text_sprite::Builder letter_builder(sans30);
    letter_builder << std::to_string(model_.get_player().get_health());
    health_sprite.reconfigure(letter_builder);
    set.add_sprite(health_sprite, board_to_screen({2,0}), 4);

    ge211::Text_sprite::Builder other_builder(sans30);
    other_builder << std::to_string(model_.get_player().get_score());
    score_sprite.reconfigure(other_builder);
    set.add_sprite(score_sprite, board_to_screen({7,0}), 4);

    //set.add_sprite(left_sprite, board_to_screen({5,6}), 3);
    set.add_sprite(trophy_sprite, board_to_screen(model_.get_trophy()), 6);

    ge211::Text_sprite::Builder winner_builder(sans30);
    winner_builder << "You Have Won! Congrats";
    win_sprite.reconfigure(winner_builder);
    std::vector<int> Pos ={model_.get_trophy().x, model_.get_trophy().y};
    if (model_.get_player().get_position() == Pos){
        set.add_sprite(win_sprite, board_to_screen({3,5}), 10);
    }

    ge211::Text_sprite::Builder loser_builder(sans30);
    loser_builder << "You Have lost! try again.";
    lose_sprite.reconfigure(loser_builder);
    if (model_.get_player().get_health() == 0){
        set.add_sprite(lose_sprite, board_to_screen({3,5}), 10);
    }




}


ge211::Dims<int>
View::initial_window_dimensions() const {
    return ge211::Dims<int> {12 * grid_size, 9 * grid_size};
}


ge211::Posn<int>
View::board_to_screen(ge211::Posn<int> posn) const {
    return { grid_size * posn.x , grid_size *posn.y };
}