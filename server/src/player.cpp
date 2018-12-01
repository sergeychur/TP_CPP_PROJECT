//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "player.hpp"

Player::~Player() {
    base.reset();
    for(auto& it :unit_arr) {
        it.reset();
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
    if(unit_arr[command.unit_id] && id == command.player_id) {
        if(unit_arr[command.unit_id]->act(command)) {
            remove_unit(command.unit_id);
        }

    }
    if(!unit_num) {
        return DEAD;
    }
    return unit_num;
}

void Player::add_unit(std::shared_ptr<AbstractUnit> unit) {
    if(!unit) {
        throw std::invalid_argument("No unit to add");
    }
    unit_arr.push_back(unit);
    ++unit_num;
}

void Player::remove_unit(const size_t id) {
        if(unit_arr[id]) {
            --unit_num;
            unit_arr[id].reset();
        }
}

int Player::add_base(std::shared_ptr<NewsTaker> updater,
        std::shared_ptr<Mediator> map, const int base_x, const int base_y) {
    if(base) {
        return ALREADY_EXISTS;
    }
    if(!map) {
        throw std::invalid_argument("No map given");
    }
    if(!updater) {
        throw std::invalid_argument("No updater given");
    }
    base = std::make_shared<Base>(map, BASE_HP, base_x, base_y, id);
    base->add(updater);
    if(!base) {
        return ERR_ALLOC;
    }
    unit_arr.push_back(base);
    ++unit_num;
    return 0;
}

void Player::add_base(std::shared_ptr<AbstractBase> _base) {
    if(!_base) {
        throw std::invalid_argument("No base given");
    }
    base = _base;
    ++unit_num;
}