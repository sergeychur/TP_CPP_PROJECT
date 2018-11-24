//
// Created by sergey on 20.11.18.
//

#include <iostream>
#include <map>

#include "real_unit.hpp"

void RealUnit::get_kicked(std::vector<int>& params) {
    enum indices {
        damage = 0,
        radius,
        x,
        y,
        params_number = 4
    };
    if(params.size() != params_number) {
        throw(std::invalid_argument("not enough params"));
    }

    if(((params[x] * params[x] - unit_x * unit_x) +
        (params[y] * params[y] - unit_y * unit_y)) <=
        params[radius] * params[radius]) {
        HP -= params[damage];
    }
    std::cout << "HP: " << HP << std::endl;

}

typedef void (RealUnit::*UnitMethod)(std::vector<int>&);

void RealUnit::react_on_command(const std::string& func_name, std::vector<int>& params) {
    std::map<std::string, UnitMethod> funcs = {
            {"get_kicked", &RealUnit::get_kicked}
    };
    auto it = funcs.find(func_name);
    if(it != funcs.end()) {
        (this->*it->second)(params);
    }
}