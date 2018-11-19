//
// Created by sergey on 28.10.18.
//

/*
    Class, that makes new units
*/

#ifndef SERVER_BASE_HPP
#define SERVER_BASE_HPP

#include "abstract_base.hpp"

class Base : public AbstractBase, RealUnit{
public:
    Base(Mediator* med, const int& HP, const int& _x,
            const int& _y, const size_t& player_id) : AbstractBase(med), RealUnit(player_id, 0, HP, _x, _y), map(med),
            unit_to_return(nullptr),  units_made(0), is_making(false) {};
    bool is_alive() override {return HP > 0;}    // change for smth normal, like HP != 0
    bool is_ready() override;
    void start_making(std::vector<int>&) override;    // init the making process
    /*const int& x, const int& y, const int& HP, const int& damage,
                      const int& speed, const bool& if_start*/
    Unit* get_unit() override;
    int interact(const std::string&, std::vector<int>&) override;   // to get kicked
    ~Base() override = default;
private:
    std::chrono::time_point<std::chrono::system_clock> start;
    Mediator* map;
    double time_to_build;     // change later
    static constexpr double default_time_to_build = 8.0;     // change later
    Unit* unit_to_return;
    size_t units_made;
    bool is_making;

    bool is_ready_for_time(const double& elapsed_time);
    void get_kicked(std::vector<int> params);   // probably take to abstract base, but... it is pure virtual
};

#endif //SERVER_BASE_HPP
