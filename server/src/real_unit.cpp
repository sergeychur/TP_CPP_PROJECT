//
// Created by sergey on 20.11.18.
//

#include <iostream>
#include <map>

#include "real_unit.hpp"

int RealUnit::get_kicked(std::vector<int>&) {
    return 0;
}

typedef int (RealUnit::*UnitMethod)(std::vector<int>&);

int RealUnit::react_on_command(const std::string& func_name, std::vector<int>& params) {
    std::map<std::string, UnitMethod> funcs = {
            {"get_kicked", &RealUnit::get_kicked}
    };
    auto it = funcs.find(func_name);
    if(it != funcs.end()) {
        return (this->*it->second)(params);
    }
    return 0;
}