//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "player.hpp"

Player::~Player() {
    if(base) {
        delete base;
    }
    for(auto& it :unit_arr) {
        delete it;
    }
    unit_arr.clear();
}

size_t Player::act(Command& command) {
    if(!base->is_alive()) {
        --unit_num;
    } else if(base->is_ready()) {
        try {
            add_unit(base->get_unit());
        } catch(std::invalid_argument& e) {
            throw e;
        }
    }
    if(command.unit_id == BASE) {
        if(base) {
            try {
                base->start_making(command.parameters);
            } catch(std::bad_alloc& e) {
                throw e;
            }
        }
        return unit_num;
    }
    if(unit_arr[command.unit_id - 1] && id == command.player_id) {
        if(unit_arr[command.unit_id - 1]->act(command)) {
            remove_unit(command.unit_id);
        }

    }
    if(!unit_num) {
        return DEAD;
    }
    return unit_num;
}

void Player::add_unit(AbstractUnit* unit) {
    if(!unit) {
        throw std::invalid_argument("No unit to add");
    }
    unit_arr.push_back(unit);
    ++unit_num;
}

void Player::remove_unit(const size_t id) {
    if(unit_arr[id - 1]) {
        delete(unit_arr[id - 1]);
        unit_arr[id - 1] = nullptr;
        --unit_num;
    }
}

int Player::add_base(NewsTaker* updater, Mediator* map, const int base_x, const int base_y) {
    if(base != nullptr) {
        return ALREADY_EXISTS;
    }
    if(!map) {
        throw std::invalid_argument("No map given");
    }
    if(!updater) {
        throw std::invalid_argument("No updater given");
    }
    base = new Base(map, BASE_HP, base_x, base_y, id);
    base->add(updater);
    if(!base) {
        return ERR_ALLOC;
    }
    ++unit_num;
    return 0;
}

void Player::add_base(AbstractBase* _base) {
    if(!_base) {
        throw std::invalid_argument("No base given");
    }
    base = _base;
    ++unit_num;
}