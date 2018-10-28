//
// Created by sergey on 19.10.18.
//

/*
    The interface for entity, that makes interaction between units, "Mediator" pattern
 */

#ifndef SERVER_MEDIATOR_HPP
#define SERVER_MEDIATOR_HPP

#include <vector>

#include "parameter.hpp"


class Mediator {
    public:
        virtual void make_interaction(std::vector<int>& param_vector) = 0;
        virtual ~Mediator() = default;
};


#endif //SERVER_MEDIATOR_HPP
