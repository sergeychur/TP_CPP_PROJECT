//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_ABSTRACT_BASE_HPP
#define SERVER_ABSTRACT_BASE_HPP

#include <chrono>

#include "unit.hpp"

class AbstractBase : public Colleague, RealUnit{
public:
    AbstractBase(Mediator* med, const int& HP, const int& _x,const int& _y, const int& id = 0) : Colleague(med), RealUnit(id, HP, _x, _y) {};
    virtual bool is_alive() = 0;
    virtual void start_making(const int& x, const int& y, const int& HP, const int& damage,
                      const int& speed, const bool& if_start) = 0;    // init the making process
    virtual Unit* get_unit(std::chrono::time_point<std::chrono::system_clock>& time) = 0;   // this returns Unit, when it's made
    // int interact(std::vector<int>&) override;   // to get kicked
    ~AbstractBase() override = default;
};

#endif //SERVER_ABSTRACT_BASE_HPP
