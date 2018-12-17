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

#include "command.hpp"


class Mediator;

class Colleague {
 protected:
	std::shared_ptr<Mediator> mediator;
 public:
	explicit Colleague(const std::shared_ptr<Mediator> &_mediator) : mediator(_mediator) {}

	virtual bool interact(Command &) = 0;

	virtual void die() = 0;

	virtual ~Colleague() = default;
};

class Mediator {
 public:
	virtual void add_colleague(const std::shared_ptr<Colleague> &,
							   size_t player_id, size_t unit_id) = 0;

	virtual bool make_interaction(Command &) = 0;

	virtual void delete_colleague(size_t player_id, size_t unit_id) = 0;

	virtual ~Mediator() = default;
};


#endif        //  SERVER_MEDIATOR_HPP
