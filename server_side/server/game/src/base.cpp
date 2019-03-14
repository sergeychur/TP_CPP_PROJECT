//
// Created by sergey on 15.11.18.
//

#include <iostream>
#include <map>
#include <numeric>


#include "handler.hpp"
#include "base.hpp"
#include "state.hpp"

Base::Base(std::shared_ptr<Mediator> med, const int HP, const int _x,
		   const int _y, const size_t player_id) : AbstractBase(med), RealUnit(player_id, 0, HP, _x, _y),
												   time_to_build(default_time_to_build), units_made(0),
												   is_making(false), is_start(false) {}

void Base::add_act_handler(std::shared_ptr<AbstractHandler> &handler) {
	act_handlers.emplace_back(handler);
}

bool Base::is_ready() {
	auto now = std::chrono::system_clock::now();
	if (is_making) {
		auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(now - start);
		return is_ready_for_time(elapsed_time.count());
	}
}

bool Base::is_ready_for_time(const double elapsed_time) {
	return elapsed_time >= time_to_build;
}

void Base::die() {
	mediator->delete_colleague(player_id, unit_id);
}

bool Base::start_making(Command &com) {
	enum indices {
		x = 0,
		y,
		HP,
		damage,
		radius,
		speed,
		if_start,
		params_size = 7
	};
	if (com.parameters.size() != params_size) {
		return false;
	}
	time_to_build = (com.parameters[if_start]) ? 0 : default_time_to_build;
	com.parameters.erase(com.parameters.begin() + if_start);
	int sum = 0;
	if ((sum = std::accumulate(com.parameters.begin() + HP, com.parameters.end(), 0)) > max_possible) {
		com.parameters[HP] -= (sum - max_possible);
		if (!com.parameters[HP]) {
			com.parameters[HP] = 0;
		}
	}
	try {
		unit_to_return = std::make_shared<Unit>(player_id, ++units_made, com.parameters[HP], com.parameters[x],
												com.parameters[y], com.parameters[damage],
												com.parameters[radius], com.parameters[speed], 0, mediator);
	} catch (std::bad_alloc &e) {
		throw e;
	}
	is_making = true;
	is_start = if_start;
	start = std::chrono::system_clock::now();
	unit_to_return->add(updater);
	add_kick_handler(unit_to_return);
	add_moving_handler(unit_to_return);
	add_pop_handler(unit_to_return);
	add_check_handler(unit_to_return);
	add_get_kicked_handler(unit_to_return);
}

std::shared_ptr<AbstractUnit> Base::get_unit() {
	if (unit_to_return) {
		mediator->add_colleague(unit_to_return, player_id, units_made);
		is_making = false;
		unit_to_return->notify();
		unit_to_return->set_notify_need(false);
		is_start = false;
		return unit_to_return;
	}
	throw std::runtime_error("No unit to return");
}

bool Base::interact(Command &com) {
	bool success = false;
	auto it = act_handlers.begin();
	while (it != act_handlers.end()) {
		if ((*it)->can_handle(com.command_name)) {
			success = (*it)->handle(com);
			it = act_handlers.end();
		} else {
			++it;
		}
	}
	notify();
	return success;
}

void Base::notify() {
	UpdateLine line(player_id, unit_id, HP, unit_x, unit_y, 0, NONE, is_alive());

	updater->handle_event(line);
}

void Base::add(std::shared_ptr<NewsTaker> news_taker) {
	if (!news_taker) {
		throw(std::invalid_argument("No news_taker"));
	}
	updater = news_taker;
}

void Base::remove() {
	updater = nullptr;
}

bool Base::act(Command &order) {
	auto it = act_handlers.begin();
	while (it != act_handlers.end()) {
		if ((*it)->can_handle(order.command_name)) {
			try {
				(*it)->handle(order);
			} catch(std::bad_alloc &e) {
				throw(e);
			}
			it = act_handlers.end();
		} else {
			++it;
		}
	}
	return is_alive();
}


void Base::add_moving_handler(std::shared_ptr<Unit> &unit) {
	std::function<bool(Command &)> move_func = std::bind(&Unit::move, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> motion_handler = std::make_shared<Handler<Unit>>(unit, "move", move_func);
	unit->add_act_handler(motion_handler);
}

void Base::add_kick_handler(std::shared_ptr<Unit> &unit) {
	std::function<bool(Command &)> kick_func = std::bind(&Unit::kick, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> kick_handler = std::make_shared<Handler<Unit>>(unit, "kick", kick_func);
	unit->add_act_handler(kick_handler);
}

void Base::add_pop_handler(std::shared_ptr<Unit> &unit) {
	std::function<bool(Command &)> pop_func = std::bind(&Unit::pop_command, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> pop_handler =
			std::make_shared<Handler<Unit>>(unit, "pop_command", pop_func);
	unit->add_distrib_handler(pop_handler);
}

void Base::add_check_handler(std::shared_ptr<Unit> &unit) {
	std::function<bool(Command &)> check_func =
			std::bind(&Unit::correct_state, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> check_handler =
			std::make_shared<Handler<Unit>>(unit, "check", check_func);
	unit->add_distrib_handler(check_handler);
}

void Base::add_get_kicked_handler(std::shared_ptr<Unit> &unit) {
	std::function<bool(Command &)> get_kicked_func =
			std::bind(&Unit::get_kicked, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> kick_handler = std::make_shared<Handler<Unit>>(unit, "get_kicked",
																					get_kicked_func);
	unit->add_act_handler(kick_handler);
}
