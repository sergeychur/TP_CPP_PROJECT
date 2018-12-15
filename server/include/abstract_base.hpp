//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_ABSTRACT_BASE_HPP
#define SERVER_ABSTRACT_BASE_HPP

#include <chrono>

#include "abstract_unit.hpp"

class AbstractBase : public AbstractUnit {
    public:
        explicit AbstractBase(std::shared_ptr<Mediator> med) : AbstractUnit(med) {}
        virtual bool is_alive() = 0;
        virtual bool is_ready() = 0;
        virtual bool start_making(Command&) = 0;    // init the making process
        virtual std::shared_ptr<AbstractUnit> get_unit() = 0;   // this returns Unit, when it's made
        ~AbstractBase() override = default;
};

#endif //SERVER_ABSTRACT_BASE_HPP
