//
// Created by sergey on 15.11.18.
//

#include <iostream>
#include <map>


#include "base.hpp"

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
    try {
        unit_to_return = new Unit(player_id, ++units_made, params[HP], params[x], params[y], params[damage],
                                  params[radius], params[speed], 0, mediator);
    } catch(std::bad_alloc& e) {
        throw e;
    }
    unit_to_return->add(updater);
}

Unit* Base::get_unit() {
    if(unit_to_return) {
        mediator->add_colleague(unit_to_return, player_id, units_made);
    }
    return unit_to_return;
}

void Base::interact(const std::string& command, std::vector<int>& params) {
    react_on_command(command, params);
}

void Base::notify() {
    UpdateLine line(player_id, unit_id, HP, unit_x, unit_y, 0, NONE, is_alive());
    updater->handle_event(line);
}

void Base::add(NewsTaker* news_taker) {
    if(!news_taker) {
        throw(std::invalid_argument("No news_taker"));
    }
    updater = news_taker;
}

void Base::remove() {
    updater = nullptr;
}