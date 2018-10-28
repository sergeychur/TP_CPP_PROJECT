//
// Created by sergey on 19.10.18.
//

/*
    implements the interface for the colleague part of "Mediator" pattern
 */

#ifndef SERVER_COLLEAGUE_HPP
#define SERVER_COLLEAGUE_HPP

#include "mediator.hpp"

class Colleague {
    protected:
        Mediator* mediator;
    public:
        explicit Colleague(Mediator* _mediator) : mediator(_mediator) {}
        int virtual interact(std::vector<int>&) = 0;
        virtual ~Colleague() = default;
};

#endif //SERVER_COLLEAGUE_HPP
