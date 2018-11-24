//
// Created by sergey on 19.10.18.
//

/*
 the mediator of the game, checking the legitimacy of the action and letting the units to interact
 */

#ifndef SERVER_MAP_HPP
#define SERVER_MAP_HPP

#include <vector>

#include "mediator.hpp"
#include "unit.hpp"

class Map : public Mediator {
    public:
        Map() : Mediator() {}
        Map(const Map&) = delete;
        Map(const Map&&) = delete;
        Map& operator=(const Map&) = delete;
        Map&& operator=(const Map&&) = delete;

        void add_colleague(Colleague*, const size_t player_id,
                const size_t unit_id) override;
        bool make_interaction(const size_t, const size_t,
                            const std::string&, std::vector<int>& param_vector) override;
        ~Map() override;

    private:
        std::vector<std::vector<Colleague*>> unit_matrix;
};

#endif //SERVER_MAP_HPP
