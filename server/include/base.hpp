//
// Created by sergey on 28.10.18.
//

#ifndef SERVER_BASE_HPP
#define SERVER_BASE_HPP

#include <chrono>

#include "unit.hpp"

class Base : public RealUnit{
    public:
        Base(Mediator* med, const int& HP, const int& _x,const int& _y, const int& id = 0);
        bool is_ready();
        void start_making(const int& x, const int& y, const int& HP, const int& damage,
                const int& speed, const bool& if_start);
        Unit* get_unit();
    private:
        std::chrono::time_point<std::chrono::system_clock> start, end;
        bool is_ready_for_time(const int& elapsed_time);
        static const int time_to_build = 1;     // change later
};

#endif //SERVER_BASE_HPP
