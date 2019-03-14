//
// Created by sergey on 28.10.18.
//

/*
    Class, that makes new units
*/

#ifndef SERVER_BASE_HPP
#define SERVER_BASE_HPP

#include "abstract_base.hpp"
#include "unit.hpp"

class Base : public AbstractBase, public RealUnit {
 public:
	Base(std::shared_ptr<Mediator> med, int HP, int _x,
		 int _y, size_t player_id);

	bool is_alive() override { return HP > 0; }

	void die() override;

	bool is_ready() override;

	bool is_ready_for_time(double elapsed_time);

	bool start_making(Command &) override;    // init the making process

	std::shared_ptr<AbstractUnit> get_unit() override;

	bool interact(Command &) override;   // to get kicked

	void notify() override;

	void add(std::shared_ptr<NewsTaker> news_taker) override;

	void remove() override;

	void add_act_handler(std::shared_ptr<AbstractHandler> &) override;

	~Base() override = default;

 private:
	void add_moving_handler(std::shared_ptr<Unit> &);

	void add_kick_handler(std::shared_ptr<Unit> &);

	void add_pop_handler(std::shared_ptr<Unit> &unit);

	void add_check_handler(std::shared_ptr<Unit> &unit);

	void add_get_kicked_handler(std::shared_ptr<Unit> &unit);

	std::chrono::time_point<std::chrono::system_clock> start;
	std::vector<std::shared_ptr<AbstractHandler>> act_handlers;
	double time_to_build;
	static constexpr double default_time_to_build = 4.0;
	std::shared_ptr<NewsTaker> updater;
	std::shared_ptr<Unit> unit_to_return;
	size_t units_made;
	bool is_making;
	bool is_start;
	static const int max_possible = 100000;

	bool act(Command &order) override;

	void add_distrib_handler(std::shared_ptr<AbstractHandler> &) override {}
};

#endif        //  SERVER_BASE_HPP
