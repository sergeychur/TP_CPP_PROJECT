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
    STILL_ACT = 0,
    BASE_HP = 100
};

enum Units {
    BASE = 0
};

class Player {
    private:
        size_t id;
        std::vector<AbstractUnit*> unit_arr;     // the array of player's units
        int add_unit(AbstractUnit*);    // adds new unit after it is made
        int remove_unit(const int& id); // removes unit by id when it is dead
        int add_base(const int& base_x, const int& base_y);
        AbstractBase* base;

    public:
        Player(Mediator* med, const int& _x, const int& _y, const size_t& player_id); /*: id(player_id),  base(med, BASE_HP, _x,_y, 0) */
        Player(const int& player_id, AbstractUnit*, AbstractBase*); // rewrite, it's bad, in tests change for add_unit, add_base
        int act(std::vector<Command>);
};

#endif //SERVER_PLAYER_HPP
