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

enum {
    ALLOWED_LINEAR_DELTA = 5,
    ALLOWED_ALPHA_DELTA = 3
};

class Unit : public AbstractUnit, public RealUnit {
    public:
        Unit(const size_t _player_id_, const size_t _unit_id, const int _HP, const int _unit_x,
                const int _unit_y, const int damage,
                const int radius, const int speed, const int look_angle, Mediator* mediator);
        Unit() = delete;
        Unit(const Unit&&) = delete;
        Unit(const Unit&) = delete;
        Unit& operator=(Unit&) = delete;
        Unit&& operator=(Unit&&) = delete;
        ~Unit() override = default;
        void add(NewsTaker* news_taker) override;
        void remove() override;
        void notify() override;
        bool act(Command& order) override;
        size_t hash_self() const;

        bool move(std::vector<int>&);
        bool move_for_time(std::vector<int>&, const double);
        bool kick(std::vector<int>&);

    private:
        void add_command(Command&);
        void correct_state(std::vector<int>&);
        void interact(const std::string&, std::vector<int>&) override;
        void perform_existing_commands();
        bool is_alive() const;

        std::queue<Command> commands;
        NewsTaker* updater;

        int damage;
        int radius;
        int speed;
        int look_angle;

        int state;

        std::chrono::time_point<std::chrono::system_clock> prev_time;
};


bool operator== (const Unit&, const Unit&);

#endif //SERVER_UNIT_HPP