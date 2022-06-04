#include "model.hxx"
#include <catch.hxx>


TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

TEST_CASE("winning game"){
    Model m(Model::vector_of_doors {{true, {2,1}, {1,8}}},
            Model::vector {{4,7},{5,7},{6,7},
                           {7,7},{8,7},{4,8},
                           {5,8},{6,8},{7,8},
                           {8,8},{10,3},{11,3},
                           {10,4},{11,4},{10,5}
                    ,{11,5},{10,6},{11,6}},        // coin
            std::vector<Shooter> {{'r', {0,2},{}}},         //
            // shooter
            Model::vector {},        // spike
            Model::vector {},        // treasure
            Model::Position {1,9},  //trophy
            Model::vector{{0,0},{1,0},{2,0},{3,0}
                    ,{4,0},{5,0},{6,0},{7,0}
                    ,{8,0},{9,0},{10,0},{11,0}
                    ,{0,3},{1,3},{2,3},{3,3},
                          {4,3},{5,3},{6,3},{7,3},
                          {8,3},{9,3},{0,4},{1,4},
                          {2,4},{3,4},{4,4},{5,4},
                          {6,4},{7,4},{8,4},{9,4},
                          {0,5},{1,5},{2,5},{3,5},
                          {4,5},{5,5},{6,5},{7,5},
                          {8,5},{9,5},{0,6},{1,6},
                          {2,6},{3,6},{4,6},{5,6},
                          {6,6},{7,6},{8,6},{9,6}}, // wall
            Model::vector {{}});

    CHECK(m.get_player().get_health() == 4);
    std::vector<int> pos = {1,8};
    CHECK(m.get_player().get_position() ==  pos);
    CHECK(m.get_player().get_score() == 0);

    m.set_player_acc({1,0});
    for (int i = 0; i<12;i++){
        m.move();
        for (int j = 0; j < 200;j++){
            m.on_frame(1);
        }

    }
    CHECK(m.get_player().get_score() == 50);
    pos = {11,8};
    CHECK(m.get_player().get_position() == pos);
    std::vector<Model::Position> coins = { {4, 7}, {5, 7},
                                           {6, 7}, {7, 7},
                                           {8, 7}, {10, 3},
                                           {11, 3}, {10, 4},
                                           {11, 4},{10, 5},
                                           {11, 5},{10, 6},
                                           {11, 6}};
    CHECK(m.get_coins() == coins);
    std::vector<Model::Position> arrows = {  {3, 2}, {5, 2},{7, 2}, {9, 2},
                                             {11, 2}, {1, 2} };
    CHECK(m.get_arrows() == arrows);
    m.set_player_acc({0,-1});
    for (int i =0; i<12;i++){
        m.move();
        for (int j = 0; j < 230;j++){
            m.on_frame(1);
        }
    }
    pos = {1,8};
    CHECK(m.get_player().get_position() == pos);
    //player has been hit
    CHECK(m.get_player().get_health() == 3);

    m.set_player_acc({1,0});
    for (int i = 0; i<12;i++){
        m.move();
    }

    m.set_player_acc({0,-1});
    for (int i =0; i<12;i++){
        m.move();
    }
    pos = {11, 1};
    CHECK(m.get_player().get_position() == pos);


    //check door takes you to new grid with new game elements and setup,
    // starting player at {1,8}
    m.set_player_acc({-1,0});
    for (int i =0; i<9;i++){
        m.move();
    }

    pos = {1,8};
    CHECK(m.get_player().get_position() == pos);
    //CHECK atttributes of new grid

    arrows = {};
    CHECK(m.get_arrows() == arrows);
    //check that there are treasure chests
    std::vector<Model::Position> treaure = {{0,1},{11,8}};
    CHECK(m.get_treasure() == treaure);
    std::vector<Model::Position> spikes;



    // get hit by spikes
    m.set_player_acc({1,0});
    for (int i=0; i<7;i++){
         m.move();
    }
    m.set_player_acc({0,-1});
    for (int i=0; i<6;i++){
        m.move();
    }
    m.set_player_acc({-1,0});
    for (int i=0; i<3;i++){
        m.move();
    }
    //back at the starting point with less life after hitting a spike
    // and 25 points less since they hit spikes
    pos = {1,8};
    CHECK(m.get_player().get_position() == pos);
    CHECK(m.get_player().get_health() == 2);
    CHECK(m.get_player().get_score() == 125);

    //pick up treasure at the corner
    m.set_player_acc({1,0});
    for (int i=0; i<7;i++){
        m.move();
    }
    m.set_player_acc({0,-1});
    for (int i=0; i<7;i++){
        m.move();
    }
    m.set_player_acc({-1,0});
    for (int i=0; i<5;i++){
        m.move();
    }

    //check that the score has incresed by 100
    CHECK(m.get_player().get_score() == 225);
    treaure = {{11,8}}; //just one treasure remaining
    //check that treaure vector has been altered
    CHECK(m.get_treasure() == treaure);

    // move to enter door that leads to trophy
    m.set_player_acc({1,0});
    for (int i=0; i<6;i++){
        m.move();
    }
    m.set_player_acc({0,1});
    for (int i=0; i<6;i++){
        m.move();
    }
    m.set_player_acc({1,0});
    for (int i=0; i<3;i++){
        m.move();
    }
    m.on_frame(1);
    //check that player has been transported to new position closer to trophy
    pos = {9,2};
    CHECK(m.get_player().get_position() == pos);
    //MOVE TOWARDS TROPHY
    m.set_player_acc({0,-1});
    m.move();
    m.set_player_acc({1,0});
    for (int i=0; i<6;i++){
        m.move();}

    CHECK(m.is_game_over);
    CHECK(m.get_player().get_score() == 325); //player didn't head over to the
    // second treasure chest at the bottom so points remained the same

}

TEST_CASE("losing game"){
    Model m(Model::vector_of_doors {{true, {2,1}, {1,8}}},
            Model::vector {{4,7},{5,7},{6,7},
                           {7,7},{8,7},{4,8},
                           {5,8},{6,8},{7,8},
                           {8,8},{10,3},{11,3},
                           {10,4},{11,4},{10,5}
                    ,{11,5},{10,6},{11,6}},        // coin
            std::vector<Shooter> {{'r', {0,2},{}}},         //
            // shooter
            Model::vector {},        // spike
            Model::vector {},        // treasure
            Model::Position {1,9},  //trophy
            Model::vector{{0,0},{1,0},{2,0},{3,0}
                    ,{4,0},{5,0},{6,0},{7,0}
                    ,{8,0},{9,0},{10,0},{11,0}
                    ,{0,3},{1,3},{2,3},{3,3},
                          {4,3},{5,3},{6,3},{7,3},
                          {8,3},{9,3},{0,4},{1,4},
                          {2,4},{3,4},{4,4},{5,4},
                          {6,4},{7,4},{8,4},{9,4},
                          {0,5},{1,5},{2,5},{3,5},
                          {4,5},{5,5},{6,5},{7,5},
                          {8,5},{9,5},{0,6},{1,6},
                          {2,6},{3,6},{4,6},{5,6},
                          {6,6},{7,6},{8,6},{9,6}}, // wall
            Model::vector {{}});

    //move towards top of bricks where arrows get shot
    m.set_player_acc({1,0});
    for (int i=0; i<13;i++){
        m.move();
    }
    m.set_player_acc({0,-1});
    for (int i=0; i<6;i++){
        m.move();
    }
    for (int i=0; i<8000;i++){
        m.on_frame(1);
    }
    //repeat the movement
    m.set_player_acc({1,0});
    for (int i=0; i<13;i++){
        m.move();
    }
    m.set_player_acc({0,-1});
    for (int i=0; i<6;i++){
        m.move();
    }
    for (int i=0; i<8000;i++){
        m.on_frame(1);
    }
    //repeat the movement
    m.set_player_acc({1,0});
    for (int i=0; i<13;i++){
        m.move();
    }
    m.set_player_acc({0,-1});
    for (int i=0; i<6;i++){
        m.move();
    }
    for (int i=0; i<8000;i++){
        m.on_frame(1);
    }
    //repeat the movement
    m.set_player_acc({1,0});
    for (int i=0; i<10;i++){
        m.move();
    }
    m.set_player_acc({0,-1});
    for (int i=0; i<6;i++){
        m.move();
    }
    for (int i=0; i<8000;i++){
        m.on_frame(1);
    }
    CHECK(m.get_player().get_health() == 0);//player is dead
    for (int i =0; i<2000;i++){
    m.on_frame(1);}
    CHECK(m.is_game_over);//game is over


}

//
//
//
// These tests should demonstrate your functional requirements.
//
