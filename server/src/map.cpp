//
// Created by sergey on 19.10.18.
//

#include <iostream>     // remove later

#include "map.hpp"



Map::~Map() {
    for(auto& it : unit_matrix) {
        it.clear();
    }
    unit_matrix.clear();
}

bool Map::make_interaction(const size_t player_id, const size_t unit_id,
        const std::string& command_name, std::vector<int>& param_vector) {
    if(player_id >= unit_matrix.size()) {
        return false;
    }
    if(unit_id >= unit_matrix[player_id].size()) {
        return false;
    }
    if(unit_matrix[player_id][unit_id]) {
        unit_matrix[player_id][unit_id]->interact(command_name, param_vector);
        return true;
    }
    return false;
}

void Map::add_colleague(Colleague* colleague, const size_t player_id,
                   const size_t unit_id) {
    if(!colleague) {
        throw(std::invalid_argument("No colleague to add"));
    }
    if(player_id >= unit_matrix.size()) {
        unit_matrix.resize(player_id + 1);
    }
    if(unit_id >= unit_matrix[player_id].size()) {
        unit_matrix[player_id].resize(unit_id + 1);
    }
    unit_matrix[player_id][unit_id] = colleague;
}