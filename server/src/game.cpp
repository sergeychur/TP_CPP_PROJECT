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
    player_arr.emplace_back(player_id);
    player_arr[player_id].add_base(map, _x, _y);
}

int Game::act(std::vector<Command>& commands_arr) {
    update_maker->delete_update();
    for(auto& command : commands_arr) {
        stat = player_arr[command.player_id].act(command);
    }
    return (player_arr.size() == 1) ? stat : STILL_ACT;
}

Update Game::get_update() {
    return update_maker->get_update();   // check later
}

