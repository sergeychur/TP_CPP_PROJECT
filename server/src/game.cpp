//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "game.hpp"

Game::Game(const size_t _player_num) : player_num(_player_num) {
    update_maker = new UpdateMaker();
    map =  new Map();
    avaliability.assign(player_num, NONE);
}

Game::~Game() {
    delete update_maker;
    delete map;
    for(auto& player : player_arr) {
        delete player;
    }
    player_arr.clear();
}

void Game::add_player(const std::pair<int, int>& base_coords, const size_t player_id) {

    auto player = new Player(player_id);
    player_arr.push_back(player);
    try {
        player_arr[player_id]->add_base(update_maker, map, base_coords.first, base_coords.second);
    } catch(std::invalid_argument& e) {
        throw e;
    }
    avaliability[player_id] = STILL_ACT;
}

size_t Game::act(std::vector<std::shared_ptr<Serializable>>& commands_arr) {
    update_maker->delete_update();
    size_t stat = STILL_ACT;
    for(auto& order : commands_arr) {
        Command command = *std::static_pointer_cast<Command>(order);
        if( avaliability[command.player_id] == STILL_ACT) {
            try {
                stat = player_arr[command.player_id]->act(command);
            } catch(std::exception& e) {
                throw e;
            }
            if (stat == DEAD) {
                avaliability[command.player_id] = DEAD;
                --player_num;
            }
        }
    }
    return (player_num == 1) ? stat : player_num;
}

Update* Game::get_update() {
    try {
        return update_maker->get_update();
    }
    catch(std::invalid_argument& e) {
        throw e;
    }
}

