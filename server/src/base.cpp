//
// Created by sergey on 15.11.18.
//

#include <iostream>

#include "base.hpp"

void Base::start_making(const int& x, const int& y, const int& HP, const int& damage,
                  const int& speed, const bool& if_start) {
    std::cout << x << y << HP << damage << speed << if_start << std::endl;
}

Unit* Base::get_unit(std::chrono::time_point<std::chrono::system_clock>& time) {
    std::cout << "hours since epoch: "
              << std::chrono::duration_cast<std::chrono::hours>(
                      time.time_since_epoch()).count()
              << '\n';      // remove
    return nullptr;
}

int Base::interact(std::vector<int>& params) {
    for(auto it = params.begin(); it != params.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}

