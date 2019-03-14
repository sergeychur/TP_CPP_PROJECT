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
#include "abstract_handler.hpp"

class AbstractUnit : public NewsMaker, public Colleague {
 public:
	explicit AbstractUnit(std::shared_ptr<Mediator> med) : NewsMaker(), Colleague(med) {}

	virtual bool act(Command &order) = 0;

	virtual bool is_alive() = 0;

	virtual void add_act_handler(std::shared_ptr<AbstractHandler> &) = 0;

	virtual void add_distrib_handler(std::shared_ptr<AbstractHandler> &) = 0;

	~AbstractUnit() override = default;
};

#endif        //  SERVER_ABSTRACT_UNIT_HPP
