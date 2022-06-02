//
// Created by Brighton Sibanda on 5/30/22.
//

#include "player.hxx"

Player::Player()
    : current_pos({1,8}),
      health(4),
      score(0),
      velocity({0,0}),
      acceleration({0, 0})


{}

std::vector<int>
Player::get_position(){
    return current_pos;
}
int
Player::get_health(){
    return health;
}
float
Player::get_score () {
    return score;
}
std::vector<int>
Player::get_velocity(){
    return velocity;
}
std::vector<int>
Player::get_acceleration(){
    return acceleration;
}
void
Player::reduce_health(){
    health -= 1;
}
void
Player::set_score(float change){
    score += change;
}
void
Player::set_acceleration(std::vector<int> change){

  acceleration = change;}

void
Player::set_pos(int a, int b){
    current_pos[0] = a;
    current_pos[1] = b;
}
void
Player::set_velocity(std::vector<int> velocityy){
    velocity = velocityy;
}
