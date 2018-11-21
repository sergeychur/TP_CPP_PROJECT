//
// Created by sergey on 20.11.18.
//

#include <iostream>
#include <exception>
#include <map>
#include <cmath>



#include "unit.hpp"

Unit::Unit(const size_t& _player_id, const size_t& _unit_id, const int& _HP, const int& _unit_x,
        const int& _unit_y, const int& _damage, const int& _radius,
     const int& _speed, const int& _look_angle, Mediator* mediator) : AbstractUnit(mediator), RealUnit(_player_id,
             _unit_id, _HP, _unit_x, _unit_y), damage(_damage), radius(_radius), speed(_speed), look_angle(_look_angle) {
}

void Unit::add(NewsTaker* news_taker) {
    if(!news_taker) {
        throw std::invalid_argument("No news_taker to add");
    }
    updater = news_taker;
}

void Unit::remove() {
    updater = nullptr;
}

void Unit::notify() {
    UpdateLine line(player_id, unit_id, HP, unit_x, unit_y, look_angle, is_alive());
    updater->handle_event(line);
}

bool Unit::is_alive() const {
    return HP > 0;

}

bool Unit::move(std::vector<int>& dest) {
    enum {
        x = 0,
        y
    };
    auto now = std::chrono::system_clock::now();
    const double time_passed = (now - prev_time).count();
    unit_x += speed * static_cast<int>((dest[x] - unit_x) / sqrt((dest[x] - unit_x) *
            (dest[x] - unit_x) + (dest[y] - unit_y) * (dest[y] - unit_y)) * time_passed);
    unit_y += speed * static_cast<int>((dest[y] - unit_y) / sqrt((dest[x] - unit_x) *
            (dest[x] - unit_x) + (dest[y] - unit_y) * (dest[y] - unit_y)) * time_passed);
    return (unit_x - dest[x]) < ALLOWED_DELTA && (unit_y - dest[y]) < ALLOWED_DELTA;
}

bool Unit::kick(std::vector<int>& target_params) {
    enum {
        player_id,
        unit_id
    };
    std::vector<int> kick_params;
    kick_params.push_back(damage);
    kick_params.push_back(radius);
    kick_params.push_back(unit_x);
    kick_params.push_back(unit_y);
    mediator->make_interaction(static_cast<size_t >(target_params[player_id]), static_cast<size_t>(target_params[unit_id]), "get_kicked", kick_params);
    return false;
}

typedef bool (Unit::*UnitMethod)(std::vector<int>&);

void Unit::perform_existing_commands() {
    std::map<std::string, UnitMethod> funcs = {
            {"move", &Unit::move},
            {"kick", &Unit::kick}
    };
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
        x,
        y
    };
    if(abs(unit_x - parameters[x]) < ALLOWED_DELTA) {
        unit_x = parameters[x];
    }
    if(abs(unit_y - parameters[y]) < ALLOWED_DELTA) {
        unit_y = parameters[y];
    }
    notify();
}
int Unit::interact(const std::string& command, std::vector<int>& params) {
    return react_on_command(command, params);
}
