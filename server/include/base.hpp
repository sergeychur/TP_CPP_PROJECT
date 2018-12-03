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
    Base(std::shared_ptr<Mediator> med, const int& HP, const int _x,
            const int _y, const size_t player_id);
    bool is_alive() override {return HP > 0;}
    bool is_ready() override;
    bool is_ready_for_time(const double elapsed_time);
    void start_making(std::vector<int>&) override;    // init the making process
    std::shared_ptr<Unit> get_unit() override;
    bool interact(const std::string&, std::vector<int>&) override;   // to get kicked
    void notify() override;
    void add(std::shared_ptr<NewsTaker> news_taker) override;
    void remove() override;

    ~Base() override = default;

private:
    std::chrono::time_point<std::chrono::system_clock> start;
    double time_to_build;
    static constexpr double default_time_to_build = 8.0;
    std::shared_ptr<NewsTaker> updater;
    std::shared_ptr<Unit> unit_to_return;
    size_t units_made;
    bool is_making;
    const static int max_possible = 1000;

    bool act(Command& order) override;
};

#endif //SERVER_BASE_HPP
