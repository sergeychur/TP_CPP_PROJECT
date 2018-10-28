//
// Created by sergey on 19.10.18.
//

/*
    the entity of player, modelling the client
*/

#ifndef SERVER_PLAYER_HPP
#define SERVER_PLAYER_HPP

#include <memory>
#include <queue>
#include <vector>
#include <iostream>

#include "unit.hpp"
#include "command.hpp"
#include "base.hpp"

enum Constants {
    DEAD = 1,
    STILL_ACT = 0
};

enum Units {
    BASE = 0
};

class Player {
    private:
        int id;
        std::vector<AbstractUnit*> unit_arr;     // the array of player's units
        int add_unit(Unit*);    // adds new unit after it is made
        int remove_unit(const int& id); // removes unit by id when it is dead
        Base base;

    public:
        int act(std::vector<Command>);
};

#endif //SERVER_PLAYER_HPP
