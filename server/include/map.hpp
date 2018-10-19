//
// Created by sergey on 19.10.18.
//

/*
 the mediator of the game, checking the legitimacy of the action and letting the units to interact
 */

#ifndef SERVER_MAP_HPP
#define SERVER_MAP_HPP

#include <string>

#include "mediator.hpp"
#include "unit.hpp"

class Map : public Mediator {
    public:
        Map(const std::string& path_to_file);
        Map(const Map&) = delete;
        Map(const Map&&) = delete;
        Map& operator=(const Map&) = delete;
        Map&& operator=(const Map&&) = delete;

        void make_interaction(std::vector<Parameter*>& param_vector) override;      // gets the vector of parameters and by them calls the alter methods of influenced objects
        ~Map() override;

    private:
        std::map<std::pair<int, int>, Unit*> unit_map;  // something that gets unit by coordinates
};

#endif //SERVER_MAP_HPP
