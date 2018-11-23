//
// Created by sergey on 19.10.18.
//

/*
    the entity of player, modelling the client
*/

#ifndef SERVER_PLAYER_HPP
#define SERVER_PLAYER_HPP

#include <vector>

#include "unit.hpp"
#include "command.hpp"
#include "base.hpp"

enum Constants {
    DEAD = 1,
    STILL_ACT = 0,
    NONE = 2,
    BASE_HP = 100,
    ALREADY_EXISTS = -1,
    ERR_ALLOC = -2
};

enum Units {
    BASE = 0
};

class Player {
    private:
        size_t id;
        std::vector<AbstractUnit*> unit_arr;     // the array of player's units
        void remove_unit(const size_t id); // removes unit by id when it is dead
        AbstractBase* base;
        size_t unit_num;

    public:
        explicit Player(const size_t player_id) : id(player_id),
                        base(nullptr), unit_num(0) {}
        size_t act(Command&);
        int add_base(NewsTaker* updater, Mediator* med, const int base_x, const int base_y);
        void add_base(AbstractBase*);
        void add_unit(AbstractUnit*);    // adds new unit after it is made

        ~Player();
};

#endif //SERVER_PLAYER_HPP
