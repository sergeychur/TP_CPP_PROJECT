//
// Created by sergey on 19.10.18.
//

/*
 the mediator of the game, checking the legitimacy of the action and letting the units to interact
 */

#ifndef SERVER_MAP_HPP
#define SERVER_MAP_HPP

#include <string>
#include <vector>

#include "mediator.hpp"
#include "unit.hpp"
#include "building.hpp"

class Map : public Mediator {
    public:
        Map(const std::string& path_to_file);
        Map(const Map&) = delete;
        Map(const Map&&) = delete;
        Map& operator=(const Map&) = delete;
        Map&& operator=(const Map&&) = delete;

        void add_colleague(Colleague*, const int& player_id,
                const int& unit_id) override;
        bool make_interaction(std::vector<int>& param_vector) override;      // gets the vector of parameters and by them calls the alter methods of influenced objects
        ~Map() override;

    private:
        std::vector<std::vector<Colleague*>> unit_map;
        // std::vector<std::vector<AbstractBuilding*>> buildings; // dunno if necessary, no
};

#endif //SERVER_MAP_HPP
