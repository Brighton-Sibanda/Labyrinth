#pragma once

#include <ge211.hxx>
#include "player.hxx"
#include "game_elements.hxx"
#include <vector>


class Model
{

public:
    using Position = ge211::Posn<int>;
    using vector = std::vector<Position>;
    using Rectangle = ge211::Rect<int>;
    using Dimensions = ge211::Posn<int>;

    Model(Rectangle all, vector co, vector sh,
                   vector sp,
                   vector tr, std::vector<int> trophy, vector wall, Position
                   door_pos, vector arrow);


    vector coins;
    vector treasure;

    Position vec_to_pos(std::vector<int>);//converts vector to ge211 position
    void start_game(); //sets is_game_over to false
    Player get_player(); //returns the player object of the game
    std::vector<Game_element> get_elements(Position pos);//returns a vector
    // containing all the game elements at a position
    std::vector<Position> get_shooters();//returns the vector of shooter
    // positions
    std::vector<Position> get_spikes();//returns a vector of all spike positions
    void apply_elements(Position);//executes all game elements onto the player
    // if the player is in that position
    int get_element_index(std::vector<Position>, Position);//helper
    // for apply elements gets the index of a position in a position vector
    Position get_door_pos();//gets the door's position in this model
    void set_spikes(std::vector<Position>);//sets the spikes vector
    void set_door_pos(Position);//sets the door position
    void set_coins(std::vector<Position>);//sets the coin positions
    void set_treasure(std::vector<Position>);//sets the treasure positions
    void set_shooter(std::vector<Position>);//sets the shooter positions
    void set_wall(std::vector<Position>);//sets the wall positions
    std::vector<int> pos_to_vec(Position);//converts ge211 position into vector
    void set_game_over();//ends the game
    bool player_against_wall(Position pos);//checks whether player can slide up
    bool move(Dimensions dir);//moves the player in the given direction
    void on_frame(float);//advances the game by a certain amount of frames
    void change_to_hidden_place();//changes attributes of model to the hidden
    // place
    void change_to_normal_model();//reverts model back to its original
    // attributes
    int model_state = 0;


private:
    //char board_[3][3];
    //char winner_;
    //int score;

    vector spikes_;
    Rectangle all_positions_;
    std::vector<int> trophy_;
    vector shooter_;
    Player player_;
    bool is_game_over = true;
    vector wall_;
    Position door_pos;
    float time;
    vector arrows_;

};
