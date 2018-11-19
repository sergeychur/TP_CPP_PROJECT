//
// Created by sergey on 19.10.18.
//

/*
    The interface for entity, that makes interaction between units, "Mediator" pattern
 */

#ifndef SERVER_MEDIATOR_HPP
#define SERVER_MEDIATOR_HPP

#include <vector>
#include <string>


class Mediator;

class Colleague {
protected:
    Mediator* mediator;
public:
    explicit Colleague(Mediator* _mediator) : mediator(_mediator) {}
    int virtual interact(const std::string&, std::vector<int>&) = 0;
    virtual ~Colleague() = default;
};

class Mediator {
    public:
        virtual void add_colleague(Colleague*,
                const int& player_id, const int& unit_id) = 0;
        virtual bool make_interaction(std::vector<int>& param_vector) = 0;
        virtual ~Mediator() = default;
};


#endif //SERVER_MEDIATOR_HPP
