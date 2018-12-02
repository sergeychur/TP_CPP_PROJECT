//
// Created by sergey on 20.11.18.
//

#include <iostream>
#include <exception>
#include <map>
#include <cmath>

#include <boost/container_hash/hash.hpp>

#include "unit.hpp"

Unit::Unit(const size_t _player_id, const size_t _unit_id, const int _HP, const int _unit_x,
        const int _unit_y, const int _damage, const int _radius,
     const int _speed, const int _look_angle, std::shared_ptr<Mediator> mediator) : AbstractUnit(mediator), RealUnit(_player_id,
             _unit_id, _HP, _unit_x, _unit_y), damage(_damage), radius(_radius), speed(_speed), look_angle(_look_angle),
             state(NONE) {
}

void Unit::add(std::shared_ptr<NewsTaker> news_taker) {
    if(!news_taker) {
        throw std::invalid_argument("No news_taker to add");
    }
    updater = news_taker;
}

void Unit::remove() {
    updater = nullptr;
}

void Unit::notify() {

    UpdateLine line(player_id, unit_id, HP, unit_x, unit_y, look_angle, state, is_alive());
    if(updater) {
        updater->handle_event(line);
    }
}

bool Unit::is_alive() const {
    return HP > 0;

}

bool Unit::move_for_time(std::vector<int>& dest, const double time_passed) {
    enum {
        x = 0,
        y
    };
    unit_x += speed * static_cast<int>((dest[x] - unit_x) / sqrt((dest[x] - unit_x) *
            (dest[x] - unit_x) + (dest[y] - unit_y)
            * (dest[y] - unit_y)) * time_passed);
    unit_y += speed * static_cast<int>((dest[y] - unit_y) / sqrt((dest[x] - unit_x) *
                                                                 (dest[x] - unit_x) + (dest[y] - unit_y) * (dest[y] - unit_y)) * time_passed);
    return (unit_x - dest[x]) < ALLOWED_LINEAR_DELTA && (unit_y - dest[y]) < ALLOWED_LINEAR_DELTA;
}

bool Unit::move(std::vector<int>& dest) {
    auto now = std::chrono::system_clock::now();
    const double time_passed = (now - prev_time).count();
    state = MOVING;
    return move_for_time(dest, time_passed);
}

bool Unit::kick(std::vector<int>& target_params) {
    enum {
        player_id,
        unit_id,
        params_num = 2
    };
    if(target_params.size() != params_num) {
        return false;
    }
    std::vector<int> kick_params;
    kick_params.push_back(damage);
    kick_params.push_back(radius);
    kick_params.push_back(unit_x);
    kick_params.push_back(unit_y);
    mediator->make_interaction(static_cast<size_t >(target_params[player_id]), static_cast<size_t>(target_params[unit_id]), "get_kicked", kick_params);
    state = FIGHTING;
    return true;
}

typedef bool (Unit::*UnitMethod)(std::vector<int>&);

void Unit::perform_existing_commands() {
    std::map<std::string, UnitMethod> funcs = {
            {"move", &Unit::move},
            {"kick", &Unit::kick}
    };
    if(commands.empty()) {
        return;
    }
    auto it = funcs.find(commands.front().command_name);
    if(it != funcs.end()) {
        bool finished = (this->*it->second)(commands.front().parameters);
        if(finished) {
            commands.pop();
        }
    }
}

bool Unit::act(Command& order) {
    if(order.command_name == "pop_command") {
        commands.pop();
    }
    state = NONE;       // mb bugs, checkout
    perform_existing_commands();
    if(order.command_name == "check") {
        correct_state(order.parameters);
    } else {
        add_command(order);
    }
    return is_alive();
}

void Unit::add_command(Command& command) {
    commands.push(command);
}

void Unit::correct_state(std::vector<int>& parameters) {
    enum {
        HP,
        x_val,
        y_val,
        angle_val,
        params_num = 4
    };
    if(parameters.size() != params_num) {
        return;
    }
    if(/*abs(unit_x - parameters[x_val]) < ALLOWED_LINEAR_DELTA*/ true) {
        unit_x = parameters[x_val];
    }
    if(/*abs(*unit_y - parameters[y_val]) < ALLOWED_LINEAR_DELTA*/true) {
        unit_y = parameters[y_val];
    }
    look_angle = parameters[angle_val];
    notify();
}
void Unit::interact(const std::string& command, std::vector<int>& params) {
    react_on_command(command, params);
}

size_t Unit::hash_self() const {
    size_t hash = 0;
    boost::hash_combine(hash, damage);
    boost::hash_combine(hash, radius);
    boost::hash_combine(hash, speed);
    boost::hash_combine(hash, look_angle);
    return hash;
}

bool operator== (const Unit& first, const Unit& second) {
    return first.hash_self() == second.hash_self();
}
