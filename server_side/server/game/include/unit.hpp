//
// Created by sergey on 19.10.18.
//

/*
    Unit is the some entity that can interact with the world(go, fight ...)
*/

#ifndef SERVER_UNIT_HPP
#define SERVER_UNIT_HPP

#include <vector>
#include <queue>
#include <chrono>
#include <functional>

#include "update.hpp"
#include "abstract_unit.hpp"
#include "real_unit.hpp"
#include "command.hpp"
#include "abstract_handler.hpp"

class Unit : public AbstractUnit, public RealUnit {
 public:
	Unit(size_t _player_id_, size_t _unit_id, int _HP, int _unit_x,
		 int _unit_y, int damage,
		 int radius, int speed, int look_angle, std::shared_ptr<Mediator> mediator);

	~Unit() override = default;

	void add(std::shared_ptr<NewsTaker> news_taker) override;

	void remove() override;

	void notify() override;

	void set_notify_need(bool need);

	bool if_notify_need();

	bool act(Command &order) override;

	size_t hash_self() const;

	bool move(Command &);

	bool move_for_time(std::vector<int> &, double);

	bool kick(Command &);

	void add_act_handler(std::shared_ptr<AbstractHandler> &) override;

	void add_distrib_handler(std::shared_ptr<AbstractHandler> &) override;

	bool correct_state(Command &);

	bool pop_command(Command &);

	bool is_alive() override;

	void die() override;

 private:
	void add_command(Command &);

	bool interact(Command &) override;

	void perform_existing_commands();

	double diff(int dest_x, int dest_y, int source_x, int source_y);

	std::unique_ptr<Command> command;
	std::shared_ptr<NewsTaker> updater;
	std::vector<std::shared_ptr<AbstractHandler>> act_handlers;
	std::vector<std::shared_ptr<AbstractHandler>> distrib_handlers;

	int damage;
	int radius;
	int speed;
	int look_angle;
	double theor_dist;

	std::chrono::time_point<std::chrono::system_clock> prev_time;
};


bool operator==(const Unit &, const Unit &);

#endif        //  SERVER_UNIT_HPP
