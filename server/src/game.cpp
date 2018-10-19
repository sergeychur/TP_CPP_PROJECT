//
// Created by sergey on 19.10.18.
//

#include "game.hpp"

Game::Game(std::string file_name, const int& player_num) {
    std::cout << file_name << player_num << std::endl;      // remove later
}

Game::~Game() {

}

int Game::act(std::vector<std::vector<std::queue<Command>>> commands_arr) {
    for(size_t i = 0; i < commands_arr.size() && stat == STILL_ACT; ++i) {
        stat = player_arr[i]->act(commands_arr[i]);
    }
    return stat;
}

Update* Game::get_update() {
    return update_maker->get_update();   // check later

}

