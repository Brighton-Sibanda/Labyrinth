#include "game_elements.hxx"

Game_element::Game_element(bool active,
                           char type,
                           std::vector<int> pos,
                           int points)
           : active(active),
             type(type),
             pos(pos),
             points(points)
{}

