#pragma once

#include <ge211.hxx>
#include "player.hxx"
#include "game_elements.hxx"
#include "door.hxx"
#include <vector>



class Shooter{
public:
    Shooter(char,ge211::Posn<int>, std::vector<ge211::Posn<int>> );
    char type;
    ge211::Posn<int> Pos;
    std::vector<ge211::Posn<int>> arrows;
};

class Model
{

public:
    using Position = ge211::Posn<int>;
    using vector = std::vector<Position>;
    //using Dimensions = ge211::Posn<int>;
    using vector_of_doors = std::vector<Door>;

    Model(vector_of_doors door,
          vector coin,
          std::vector<Shooter> shooter,
          vector spike,
          vector treasure,
          Position trophy,
          vector wall,
          vector arrow);

    // converts vec to ge211 position
    Position vec_to_pos(std::vector<int>) const;
    // sets is_game_over to false
    //void start_game();
    // returns the player object of the game
    Player get_player() const;
    // returns a vector
    std::vector<Game_element> get_elements(Position pos);
    // containing all the game elements at a position
    std::vector<Shooter> get_shooters() const;//returns the vector of shooter
    // positions
    std::vector<Position> get_spikes() const;//returns a vector of all spike
    // positions
    void apply_elements(Position);//executes all game elements onto the player
    // if the player is in that position
    int get_element_index(std::vector<Position>, Position);//helper
    // for apply elements gets the index of a position in a position vector
    vector_of_doors get_doors() const;//gets the doors in this model
    void set_spikes(std::vector<Position>);//sets the spikes vector
    void set_doors(vector_of_doors);//sets the doors
    void set_coins(std::vector<Position>);//sets the coin positions
    void set_treasure(std::vector<Position>);//sets the treasure positions
    void set_shooter(std::vector<Shooter>);//sets the shooter positions
    void set_wall(std::vector<Position>);//sets the wall positions
    std::vector<int> pos_to_vec(Position);//converts ge211 position into vector
    void set_game_over();//ends the game
    //bool player_against_wall(Position pos);//checks whether player can
    // slide up
    bool move();//moves the player in the given direction
    void on_frame(float);//advances the game by a certain amount of frames
    void change_to_stage_1();//changes the attributes of model to the next grid
    //int model_state = 0;
    void shoot();//shoot arrows in a straight line
    void shoot_up(Shooter);
    void shoot_down(Shooter);
    void shoot_left(Shooter);
    void shoot_right(Shooter);
    vector get_wall() const;
    vector get_coins() const;
    vector get_treasure() const;
    bool good_position(Position);
    void set_player_acc(std::vector<int>);
    //void set_player_pos(std::vector<int>);
    bool is_game_over = false;
    vector get_arrows() const;
    void set_arrows(vector);
    void set_trophy(Position);
    Position get_trophy() const;




private:
    //char board_[3][3];
    //char winner_;
    //int score;

    vector_of_doors doors;
    vector coins;
    vector treasure;
    vector spikes_;
    Position trophy_;
    std::vector<Shooter> shooter_;
    Player player_;

    vector wall_;
    float time_for_points;
    vector arrows_;
    int time_total = 0;

};

