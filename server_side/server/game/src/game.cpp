//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "game.hpp"
#include "map.hpp"

Game::Game(const size_t _player_num) : player_num(_player_num) {
	update_maker = std::make_shared<UpdateMaker>();
	map = std::make_shared<Map>();
	avaliability.assign(player_num, SIMPLE);
}

Game::~Game() {
	update_maker.reset();
	map.reset();
	for (auto &player : player_arr) {
		player.reset();
	}
	player_arr.clear();
}

void Game::add_player(const std::pair<int, int> &base_coords, const size_t player_id) {
	player_arr.push_back(std::make_unique<Player>(player_id));
	try {
		player_arr[player_id]->add_base(update_maker, map, base_coords.first, base_coords.second);
	} catch (std::invalid_argument &e) {
		throw e;
	}
	avaliability[player_id] = STILL_ACT;
}

size_t Game::act(std::vector<Command> &commands_arr) {
	size_t stat = STILL_ACT;
	for (auto& it : commands_arr) {
		// if(it.command_name != "check") {
			std::cout << "Got command" << std::endl;
			std::cout << it << std::endl;
		// }
		if (player_arr.size() > it.player_id) {
			if (avaliability[it.player_id] == STILL_ACT) {
				try {
					stat = player_arr[it.player_id]->act(it);
				} catch (std::exception &e) {
					throw e;
				}
				if (stat == DEAD) {
					avaliability[it.player_id] = DEAD;
					--player_num;
				}
			}
		}
	}
	return (player_num == 1) ? stat : player_num;
}

std::unique_ptr<Update> Game::get_update() {
	try {
		return update_maker->get_update();
	}
	catch (std::invalid_argument &e) {
		throw e;
	}
}

