//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_ABSTRACT_BASE_HPP
#define SERVER_ABSTRACT_BASE_HPP

#include <chrono>
#include<tuple>

#include "unit.hpp"

class AbstractBase : public Colleague {
public:
    explicit AbstractBase(Mediator* med) : Colleague(med) {}
    virtual bool is_alive() = 0;
    virtual bool is_ready() = 0;
    virtual void start_making(std::vector<int>&) = 0;    // init the making process
    /*const int& x, const int& y, const int& HP, const int& damage,
                      const int& speed, const bool& if_start*/
    virtual Unit* get_unit() = 0;   // this returns Unit, when it's made
    ~AbstractBase() override = default;
};

#endif //SERVER_ABSTRACT_BASE_HPP
