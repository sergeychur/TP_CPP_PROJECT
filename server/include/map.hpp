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

class Map : public Mediator {
    public:
        Map() = default;
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
};

#endif //SERVER_MAP_HPP
