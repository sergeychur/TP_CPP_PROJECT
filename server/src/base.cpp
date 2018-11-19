//
// Created by sergey on 15.11.18.
//

#include <iostream>
#include <map>


#include "base.hpp"

typedef void (*func)(const std::vector<int>& params);

bool Base::is_ready() {
    auto now = std::chrono::system_clock::now();
    if(is_making) {
        return is_ready_for_time((now - start).count());
    }
    return false;
}

bool Base::is_ready_for_time(const double& elapsed_time) {
    return elapsed_time > time_to_build;
}

void Base::start_making(std::vector<int>& params) {
    enum indices {
        x = 0,
        y,
        HP,
        damage,
        speed,
        if_start
    };
    time_to_build = (params[if_start]) ? 0 : default_time_to_build;
    params.erase(params.begin() + if_start);
    unit_to_return = new Unit(player_id, ++units_made, params[HP], params[x], params[y], params[damage], params[speed], 0, map);
}

Unit* Base::get_unit() {
    return unit_to_return;
}

void Base::get_kicked(std::vector<int> params) {
    std::cout << params.size();
}

int Base::interact(const std::string& command, std::vector<int>& params) {
    std::map<std::string, func> func_map;
    std::cout << command << params.size();
    return 0;
}

