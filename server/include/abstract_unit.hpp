//
// Created by sergey on 28.10.18.
//

/*
    interface for future unit
    it takes a command and acts in some way
*/

#ifndef SERVER_ABSTRACT_UNIT_HPP
#define SERVER_ABSTRACT_UNIT_HPP

#include <string>
#include <vector>

#include "news_maker.hpp"
#include "colleague.hpp"
#include "command.hpp"

class AbstractUnit : public NewsMaker, public Colleague {
    public:
        int virtual act(Command order);
        ~AbstractUnit() override = default;
};

#endif //SERVER_ABSTRACT_UNIT_HPP
