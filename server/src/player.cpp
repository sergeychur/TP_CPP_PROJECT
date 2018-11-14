//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "player.hpp"

Player::Player(Mediator* med, const int& base_x, const int& base_y, const size_t& player_id) : id(player_id) {
    // Base(Mediator* med, const int& HP, const int& _x,const int& _y, const int& id = 0) : AbstractBase(med, HP, _x, _y, id) {};
    base = new Base(med, BASE_HP, base_x, base_y, player_id);
}

int Player::act(std::vector<Command>& command_arr) {
    std::cout << sizeof(command_arr) << std::endl;      // remove later
    return STILL_ACT;
}