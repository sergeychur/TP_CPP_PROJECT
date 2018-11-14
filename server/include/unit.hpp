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

#include "update.hpp"
#include "abstract_unit.hpp"
#include "real_unit.hpp"
#include "command.hpp"

class Unit : public AbstractUnit, public RealUnit {
    public:
        Unit(const int& _player_id_, const int& _unit_id, const int& _HP, const int _unit_x, const int& _unit_y, const int& damage,
                const int& speed, const int& look_angle, Mediator* mediator);
        Unit() = delete;
        Unit(const Unit&&);
        Unit(const Unit&) = delete;
        Unit& operator=(Unit&) = delete;
        Unit&& operator=(Unit&&);
        ~Unit() override;
        void add(NewsTaker* news_taker) override;   // adds UpdateMaker
        void remove() override;
        void notify() override;
        bool is_alive();
        int act(Command& order) override;     // here the command is parsed
                                    // it can be either real command or check command

    private:
        int add_command(const std::string& command, std::vector<int>);
        int check_truth(const int& x, const int& y, const int& look_angle, const int& HP);
        int interact(std::vector<int>&) override;   // take some damage from other units
        int change_state(const std::string state_name, const std::vector<int> changes);

        std::queue<Command> commands;
        NewsTaker* updater;

        int player_id;
        int unit_id;
        int damage;
        // int damage_radius;   // make later if long strike is available
        int speed;
        int look_angle;
};

bool operator== (const Unit&, const Unit&);

#endif //SERVER_UNIT_HPP
