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

enum constants {
    WIN = 1,
    STILL_ACT = 0
};

enum Units {
    BASE = 0
};

class Player {
    private:
        std::vector<Unit*> unit_arr;     // the array of player's units
        // Base base; in constructor write unit_arr[0] - base;

    public:
    int act(std::vector<std::queue<Command>>& commands_arr);    // giving the orders to units
};

#endif //SERVER_PLAYER_HPP
