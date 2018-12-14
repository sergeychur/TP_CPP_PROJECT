//
// Created by sergey on 19.10.18.
//

/*
    Unit is the some entity that can interact with the world(go, fight ...)
*/

#ifndef SERVER_UNIT_HPP
#define SERVER_UNIT_HPP

#include <vector>
#include <queue>
#include <chrono>
#include <functional>

#include "update.hpp"
#include "abstract_unit.hpp"
#include "real_unit.hpp"
#include "command.hpp"
#include "abstract_handler.hpp"

enum {
    ALLOWED_LINEAR_DELTA = 5,
    ALLOWED_ALPHA_DELTA = 3
};

class Unit : public AbstractUnit, public RealUnit {
    public:
        Unit(const size_t _player_id_, const size_t _unit_id, const int _HP, const int _unit_x,
                const int _unit_y, const int damage,
                const int radius, const int speed, const int look_angle, std::shared_ptr<Mediator> mediator);
        ~Unit() override = default;
        void add(std::shared_ptr<NewsTaker> news_taker) override;
        void remove() override;
        void notify() override;
        bool act(Command& order) override;
        size_t hash_self() const;

        bool move(/*std::vector<int>&*/Command&);
        bool move_for_time(std::vector<int>&, const double);
        bool kick(Command&/*std::vector<int>&*/);
        void add_act_handler(std::shared_ptr<AbstractHandler>&) override;
        void add_distrib_handler(std::shared_ptr<AbstractHandler>&) override;
        bool correct_state(Command&);
        bool pop_command(Command&);

    private:
        void add_command(Command&);
        bool interact(/*const std::string&, std::vector<int>&*/Command&) override;
        void perform_existing_commands();
        bool is_alive() const;
        double ruling_cos(const int source_x, const int source_y, const int dest_x, const int dest_y);
        double ruling_sin(const int source_x, const int source_y, const int dest_x, const int dest_y);
        double diff(const int dest_x, const int dest_y, const int source_x,  const int source_y);

        std::queue<Command> commands;
        std::shared_ptr<NewsTaker> updater;
        std::vector<std::shared_ptr<AbstractHandler>> act_handlers;
        std::vector<std::shared_ptr<AbstractHandler>> distrib_handlers;

        int damage;
        int radius;
        int speed;
        int look_angle;

        int state;

        static constexpr double dissipation = 1000;
        std::chrono::time_point<std::chrono::system_clock> prev_time;
};


bool operator== (const Unit&, const Unit&);

#endif //SERVER_UNIT_HPP
