//
// Created by sergey on 28.10.18.
//

#ifndef SERVER_ABSTRACT_UNIT_HPP
#define SERVER_ABSTRACT_UNIT_HPP

#include <string>
#include <vector>

#include "news_maker.hpp"
#include "colleague.hpp"
#include "parameter.hpp"

class AbstractUnit : public NewsMaker, public Colleague {
    int virtual add_command(const std::string& command, std::vector<int> parameters) = 0;
    bool virtual check_trurh(const int& x, const int& y, const int& look_angle, const int& HP) = 0;
    ~AbstractUnit() override = default;
};

#endif //SERVER_ABSTRACT_UNIT_HPP
