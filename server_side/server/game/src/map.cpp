//
// Created by sergey on 19.10.18.
//

#include <iostream>     // remove later

#include "map.hpp"


Map::~Map() {
	for (auto &it : unit_matrix) {
		it.clear();
	}
	unit_matrix.clear();
}

bool Map::make_interaction(Command &com) {
	if (com.player_id >= unit_matrix.size()) {
		return false;
	}
	if (com.unit_id >= unit_matrix[com.player_id].size()) {
		return false;
	}
	if (unit_matrix[com.player_id][com.unit_id].expired()) {
		return false;
	}
	auto interacted_unit = unit_matrix[com.player_id][com.unit_id].lock();
	if(!interacted_unit->interact(com)) {
		interacted_unit->die();
	}
	return true;
}

void Map::add_colleague(const std::shared_ptr<Colleague> &colleague, const size_t player_id,
						const size_t unit_id) {
	if (!colleague) {
		throw(std::invalid_argument("No colleague to add"));
	}
	if (player_id >= unit_matrix.size()) {
		unit_matrix.resize(player_id + 1);
	}
	if (unit_id >= unit_matrix[player_id].size()) {
		unit_matrix[player_id].resize(unit_id + 1);
	}
	unit_matrix[player_id][unit_id] = colleague;
}

void Map::delete_colleague(const size_t player_id, const size_t unit_id) {
	if(player_id > unit_matrix.size()) {
		return;
	}
	if(unit_id > unit_matrix[player_id].size()) {
		return;
	}
	unit_matrix[player_id][unit_id].reset();
}
