//
// Created by sergey on 20.11.18.
//

#include <iostream>

#include "unit.hpp"

Unit::Unit(const size_t& _player_id, const size_t& _unit_id, const int& _HP, const int _unit_x, const int& _unit_y, const int& _damage,
     const int& _speed, const int& _look_angle, Mediator* mediator) : AbstractUnit(mediator), RealUnit(_player_id,
             _unit_id, _HP, _unit_x, _unit_y), damage(_damage), speed(_speed), look_angle(_look_angle) {
}

void Unit::add(NewsTaker* news_taker) {
    std::cout << news_taker;
}
void Unit::remove() {}
void Unit::notify() {};
bool Unit::is_alive() {return true;}
int Unit::act(Command& order) {
    return order.parameters[0];
}

int Unit::add_command(const std::string& command, std::vector<int> params) {
    std::cout << command << params.size();
    return 0;
}
int Unit::check_truth(const int& x, const int& y, const int& look_angle, const int& HP) {
    std::cout << x << y << look_angle << HP;
    return 0;
}
int Unit::interact(const std::string& command, std::vector<int>& params) {
    std::cout << command << params.size();
    return 0;
}
int Unit::change_state(const std::string state_name, const std::vector<int> changes) {
    std::cout << state_name << changes.size();
    return 0;
}