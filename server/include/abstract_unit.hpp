//
// Created by sergey on 28.10.18.
//

/*
    interface for future unit
    it takes a command and acts in some way
*/

#ifndef SERVER_ABSTRACT_UNIT_HPP
#define SERVER_ABSTRACT_UNIT_HPP

#include "news_maker.hpp"
#include "mediator.hpp"
#include "command.hpp"

class AbstractUnit : public NewsMaker, public Colleague {
    public:
        explicit AbstractUnit(std::shared_ptr<Mediator> med) : NewsMaker(), Colleague(med) {}
        virtual bool act(Command& order) = 0;
        ~AbstractUnit() override = default;
        enum states {
            NONE = 0,
            MOVING = 1,
            FIGHTING = 2
        };
};

#endif //SERVER_ABSTRACT_UNIT_HPP
