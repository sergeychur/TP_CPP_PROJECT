//
// Created by sergey on 28.10.18.
//

/*
    Class, that makes new units
*/

#ifndef SERVER_BASE_HPP
#define SERVER_BASE_HPP

#include <chrono>

#include "abstract_base.hpp"

class Base : public AbstractBase{
public:
    Base(Mediator* med, const int& HP, const int& _x,const int& _y, const int& id = 0) : AbstractBase(med, HP, _x, _y, id) {};
    bool is_alive() override;
    void start_making(const int& x, const int& y, const int& HP, const int& damage,
                      const int& speed, const bool& if_start) override;    // init the making process
    Unit* get_unit(std::chrono::time_point<std::chrono::system_clock> time) override;   // this returns Unit, when it's made
    int interact(std::vector<int>&) override;   // to get kicked
    ~Base() override;
private:
    std::chrono::time_point<std::chrono::system_clock> start, end;
    bool is_ready_for_time(const int& elapsed_time);
    static const int time_to_build = 1;     // change later

};

#endif //SERVER_BASE_HPP