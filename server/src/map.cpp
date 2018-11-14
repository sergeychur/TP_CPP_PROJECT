//
// Created by sergey on 19.10.18.
//

#include <iostream>     // remove later

#include "map.hpp"



Map::~Map() {

}

bool Map::make_interaction(std::vector<int>& param_vector) {
    if(param_vector.size() != 0) {
        return true;
    }
    return false;
}

void Map::add_colleague(Colleague* colleague, const int& player_id,
                   const int& unit_id) {
    std::cout << colleague << player_id << unit_id << std::endl;
}