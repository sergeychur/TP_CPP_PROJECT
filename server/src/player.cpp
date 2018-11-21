//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "player.hpp"

int Player::act(Command& command) {
    int status = DEAD;
    if(base->is_ready()) {
        add_unit(base->get_unit());
    }
    if(command.unit_id == BASE) {
        base->start_making(command.parameters);
    }
    if(unit_arr[command.unit_id] && id == command.player_id) {
        if(unit_arr[command.unit_id]->act(command)) {
            remove_unit(command.unit_id);
        }

    }
    return status;
}

void Player::add_unit(AbstractUnit* unit) {
    if(!unit) {
        throw std::invalid_argument("No unit to add");
    }
    unit_arr.push_back(unit);
}

void Player::remove_unit(const size_t& id) {
    if(unit_arr[id]) {
        delete(unit_arr[id]);
        unit_arr[id] = nullptr;
    }
}

int Player::add_base(Mediator* map, const int& base_x, const int& base_y) {
    if(base != nullptr) {
        return ALREADY_EXISTS;
    }
    if(!map) {
        throw std::invalid_argument("No map given");
    }
    base = new Base(map, BASE_HP, base_x, base_y, id);
    if(!base) {
        return ERR_ALLOC;
    }
    return 0;
}

void Player::add_base(AbstractBase* _base) {
    if(!base) {
        throw std::invalid_argument("No base given");
    }
    base = _base;
}