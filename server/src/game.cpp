//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "game.hpp"

Game::Game(const size_t& player_num) {
    std::cout << player_num << std::endl;      // remove later
    update_maker = new UpdateMaker();
    map =  new Map();
}

Game::~Game() {
    std::cout << "destructor" << std::endl;
    delete update_maker;
    delete map;
}

void Game::add_player(const int& _x, const int& _y, const size_t& player_id) {
    std::cout << "added player number " <<  player_id << " with base coordinates " << _x << " " << _y << std::endl;
    player_arr.emplace_back(map, _x, _y, player_id);
}

int Game::act(std::vector<std::vector<Command>>& commands_arr) {
    for(size_t i = 0; i < commands_arr.size() && stat == STILL_ACT; ++i) {
        // deal with the situation when there is no command for player
        stat = player_arr[i].act(commands_arr[i]);
    }
    return stat;
}

Update* Game::get_update() {
    return update_maker->get_update();   // check later
}

