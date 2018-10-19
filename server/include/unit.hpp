//
// Created by sergey on 19.10.18.
//

/*
    Unit is the some entity that can interact with the world(go, fight ...)
*/

#ifndef SERVER_UNIT_HPP
#define SERVER_UNIT_HPP

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <memory>

#include "news_maker.hpp"
#include "update.hpp"
#include "skill.hpp"
#include "parameter.hpp"
#include "colleague.hpp"

class Unit : public NewsMaker, public Colleague {
    public:
        Unit(const int& _HP, std::vector<std::pair<std::string, Skill>>, Mediator* mediator);
        Unit() = delete;
        Unit(const Unit&&);
        Unit(const Unit&) = delete;
        Unit& operator=(Unit&) = delete;
        Unit&& operator=(Unit&&);
        void add(NewsTaker* news_taker) override;
        void remove() override;
        void notify() override;
        int act(const std::string& command, std::vector<Parameter>);    // interact with the world using skills

    private:
        std::map<std::string, Skill*> skills;
        std::vector<NewsTaker*> news_takers_arr;
        int HP;     // consider removing this to skill get_kicked
};

#endif //SERVER_UNIT_HPP
