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

int Map::make_interaction(const size_t& player_id, const size_t& unit_id,
        const std::string& command_name, std::vector<int>& param_vector) {
    return unit_matrix[player_id][unit_id]->interact(command_name, param_vector);
}

void Map::add_colleague(Colleague* colleague, const size_t& player_id,
                   const size_t& unit_id) {
    if(player_id > unit_matrix.size()) {
        unit_matrix.resize(player_id + 1);
    }
    if(unit_id > unit_matrix[player_id].size()) {
        unit_matrix[player_id].resize(unit_id + 1);
    }
    unit_matrix[player_id][unit_id] = colleague;
}