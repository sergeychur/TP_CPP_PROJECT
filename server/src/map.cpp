//
// Created by sergey on 19.10.18.
//

#include <iostream>     // remove later

#include "map.hpp"

Map::Map(const std::string &path_to_file) {
    std::cout << path_to_file << std::endl;
}

Map::~Map() {

}

void Map::make_interaction(std::vector<int>& param_vector) {
    if(param_vector.size() != 0) {
        return;
    }
}