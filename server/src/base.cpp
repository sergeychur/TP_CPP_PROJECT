//
// Created by sergey on 15.11.18.
//

#include <iostream>
#include <map>
#include <numeric>

#include "base.hpp"

Base::Base(std::shared_ptr<Mediator> med, const int& HP, const int _x,
    const int _y, const size_t player_id) : AbstractBase(med), RealUnit(player_id, 0, HP, _x, _y),
    time_to_build(default_time_to_build),/*
    updater(nullptr),
    unit_to_return(nullptr), */ units_made(0), is_making(false) {
};

bool Base::is_ready() {
    auto now = std::chrono::system_clock::now();
    if(is_making) {
        return is_ready_for_time((now - start).count());
    }
    return false;
}

bool Base::is_ready_for_time(const double elapsed_time) {
    return elapsed_time > time_to_build;
}

void Base::start_making(std::vector<int>& params) {
    enum indices {
        x = 0,
        y,
        HP,
        damage,
        radius,
        speed,
        if_start,
        params_size = 7
    };
    if(params.size() != params_size) {
        return;
    }
    time_to_build = (params[if_start]) ? 0 : default_time_to_build;
    params.erase(params.begin() + if_start);
    int sum = 0;
    if((sum = std::accumulate(params.begin() + HP, params.end(), 0)) > max_possible) {
        params[HP] -= (sum - max_possible);
        if(!params[HP]) {
            params[HP] = 0;
        }
    }
    try {
        unit_to_return = std::make_shared<Unit>(player_id, ++units_made, params[HP], params[x], params[y], params[damage],
                                  params[radius], params[speed], 0, mediator);
    } catch(std::bad_alloc& e) {
        throw e;
    }
    is_making = true;
    unit_to_return->add(updater);
}

std::shared_ptr<Unit> Base::get_unit() {
    if(unit_to_return) {
        mediator->add_colleague(unit_to_return, player_id, units_made);
    }
    is_making = false;
    return unit_to_return;
}

bool Base::interact(const std::string& command, std::vector<int>& params) {
    bool success = react_on_command(command, params);
    notify();
    return success;
}

void Base::notify() {
    UpdateLine line(player_id, unit_id, HP, unit_x, unit_y, 0, NONE, is_alive());
    updater->handle_event(line);
}

void Base::add(std::shared_ptr<NewsTaker> news_taker) {
    if(!news_taker) {
        throw(std::invalid_argument("No news_taker"));
    }
    updater = news_taker;
}

void Base::remove() {
    updater = nullptr;
}

typedef void (Base::*BaseMethod)(std::vector<int>&);

bool Base::act(Command& order) {
    std::map<std::string, BaseMethod> funcs = {
            {"create_unit", &Base::start_making},
    };
    auto it = funcs.find(order.command_name);
    if(it != funcs.end()) {
        try {
            (this->*it->second)(order.parameters);
        } catch(std::bad_alloc& e) {
            throw(e);
        }
    }
    return is_alive();
}
