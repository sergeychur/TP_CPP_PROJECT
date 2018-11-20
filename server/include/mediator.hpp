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
    virtual int interact(const std::string&, std::vector<int>&) = 0;
    virtual ~Colleague() = default;
};

class Mediator {
    public:
        virtual void add_colleague(Colleague*,
                const size_t& player_id, const size_t& unit_id) = 0;
        virtual int make_interaction(const size_t&, const size_t&,
                const std::string&, std::vector<int>& param_vector) = 0;
        virtual ~Mediator() = default;
};


#endif //SERVER_MEDIATOR_HPP
