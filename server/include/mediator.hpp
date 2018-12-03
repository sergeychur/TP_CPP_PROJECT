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
#include <memory>


class Mediator;

class Colleague {
protected:
    std::shared_ptr<Mediator> mediator;
public:
    explicit Colleague(const std::shared_ptr<Mediator>& _mediator) : mediator(_mediator) {}
    virtual bool interact(const std::string&, std::vector<int>&) = 0;
    virtual ~Colleague() = default;
};

class Mediator {
    public:
        virtual void add_colleague(const std::shared_ptr<Colleague>&,
                const size_t player_id, const size_t unit_id) = 0;
        virtual bool make_interaction(const size_t, const size_t,
                const std::string&, std::vector<int>& param_vector) = 0;
        virtual ~Mediator() = default;
};


#endif //SERVER_MEDIATOR_HPP
