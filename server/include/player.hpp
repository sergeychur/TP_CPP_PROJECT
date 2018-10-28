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
    WIN = 1,
    STILL_ACT = 0
};

enum Units {
    BASE = 0
};

class Player {
    private:
        int id;
        std::vector<AbstractUnit*> unit_arr;     // the array of player's units
        int add_unit(Unit*);
        int remove_unit(const int& id);
        Base base;

    public:
    int add_commands(std::vector<Command>& commands_arr);    // giving the orders to units
    int check_truth(std::vector<std::vector<int>>& params);    // here the params to check(at first coordinates of units) come, change for some checker struct
};

#endif //SERVER_PLAYER_HPP
