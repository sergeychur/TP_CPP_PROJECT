//
// Created by sergey on 28.10.18.
//

#ifndef SERVER_BASE_HPP
#define SERVER_BASE_HPP

#include "unit.hpp"

class Base {
    public:
        Base() = default;
        bool is_ready() const {return ready;}
        void start_making(const int& x, const int& y, const int& HP, const int& damage,
                const int& speed, const bool& if_start);
        Unit* get_unit();
    private:
        bool ready;
        int time;   // choose correct type later
};

#endif //SERVER_BASE_HPP
