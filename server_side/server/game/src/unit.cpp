//
// Created by sergey on 20.11.18.
//

#include <iostream>
#include <exception>
#include <map>
#include <cmath>

#include <boost/container_hash/hash.hpp>


#include "handler.hpp"
#include "unit.hpp"

Unit::Unit(const size_t _player_id, const size_t _unit_id, const int _HP, const int _unit_x,
		   const int _unit_y, const int _damage, const int _radius,
		   const int _speed, const int _look_angle, std::shared_ptr<Mediator> mediator) : AbstractUnit(mediator),
																						  RealUnit(_player_id,
																								   _unit_id, _HP,
																								   _unit_x, _unit_y),
																						  damage(_damage),
																						  radius(_radius),
																						  speed(_speed),
																						  look_angle(_look_angle),
																						  theor_dist(0) {
	state.set_notify_need(true);
}

void Unit::add(std::shared_ptr<NewsTaker> news_taker) {
	if (!news_taker) {
		throw std::invalid_argument("No news_taker to add");
	}
	updater = news_taker;
}

void Unit::remove() {
	updater = nullptr;
}

void Unit::notify() {
	if (if_notify_need()) {
		UpdateLine line(player_id, unit_id, HP, unit_x, unit_y, look_angle, state.get_state(), is_alive());
		if (updater) {
			updater->handle_event(line);
		}
	}
}

void Unit::set_notify_need(bool need) {
	state.set_notify_need(need);
}

bool Unit::if_notify_need() {
	return state.if_notify_need();
}

bool Unit::is_alive() {
	return HP > 0;
}

void Unit::die() {
	mediator->delete_colleague(player_id, unit_id);
}

double Unit::diff(const int dest_x, const int dest_y, const int source_x, const int source_y) {
	return sqrt((dest_x - source_x) * (dest_x - source_x) + (dest_y - source_y) * (dest_y - source_y));
}

bool Unit::move_for_time(std::vector<int> &dest, const double time_passed) {
	enum {
		x = 0,
		y = 1,
		params_num = 2
	};
	if (dest.size() != 2) {
		throw std::invalid_argument("Wrong number of params in move unit func");
	}
	theor_dist += speed * time_passed;
	return diff(dest[x], dest[y], unit_x, unit_y) < allowed_linear_delta;
}

bool Unit::move(Command &com) {
	theor_dist = 0;
	auto now = std::chrono::system_clock::now();
	const double time_passed = std::chrono::duration_cast<std::chrono::seconds>(now - prev_time).count();
	state.make_moving();
	return move_for_time(com.parameters, time_passed);
}

bool Unit::kick(Command &com) {
	enum {
		player_id,
		unit_id,
		params_num = 2
	};
	if (com.parameters.size() != params_num) {
		return false;
	}
	std::vector<int> kick_params;
	kick_params.push_back(damage);
	kick_params.push_back(radius);
	kick_params.push_back(unit_x);
	kick_params.push_back(unit_y);
	Command com_to_pass(static_cast<size_t >(com.parameters[player_id]),
			static_cast<size_t>(com.parameters[unit_id]),
						"get_kicked", kick_params);
	bool success = mediator->make_interaction(com_to_pass);
	if (success) {
		state.make_fighting();
	}
	command.reset();
	return true;
}

void Unit::perform_existing_commands() {
	if (!command) {
		state.make_none();
		return;
	}
	set_notify_need(true);
	bool handled = false;
	auto it = act_handlers.begin();
	while (it != act_handlers.end()) {
		if ((*it)->can_handle(command->command_name)) {
			(*it)->handle(*command);
			handled = true;
			it = act_handlers.end();
		} else {
			++it;
		}
	}
	if (!handled) {
		command.reset();
	}
}

bool Unit::pop_command(Command &com) {
	command.reset();
	state.make_none();
	notify();
	set_notify_need(false);
	return true;
}

bool Unit::act(Command &order) {
	auto it = distrib_handlers.begin();
	bool handled = false;
	while (it != distrib_handlers.end() && !handled) {
		if ((*it)->can_handle(order.command_name)) {
			(*it)->handle(order);
			handled = true;
		} else {
			++it;
		}
	}

	if (!handled) {
		add_command(order);
	}
	perform_existing_commands();
	return is_alive();
}

void Unit::add_command(Command &com) {
	if (command) {
		command.reset();
	}
	set_notify_need(true);
	command = std::make_unique<Command>(com);
	prev_time = std::chrono::system_clock::now();
}

void Unit::add_act_handler(std::shared_ptr<AbstractHandler> &handler) {
	act_handlers.emplace_back(handler);
}

void Unit::add_distrib_handler(std::shared_ptr<AbstractHandler> &handler) {
	distrib_handlers.emplace_back(handler);
}

bool Unit::correct_state(Command &com) {
	enum {
		HP,
		x_val,
		y_val,
		angle_val,
		params_num = 4
	};
	if (com.parameters.size() != params_num) {
		return false;
	}
	double dist = diff(com.parameters[x_val], com.parameters[y_val], unit_x, unit_y);
	if (dist < (theor_dist + allowed_linear_delta)) {
		unit_x = com.parameters[x_val];
		unit_y = com.parameters[y_val];
	} else {
		double koef = dist / theor_dist;
		unit_x += static_cast<int>(koef * (com.parameters[x_val] - unit_x));
		unit_y += static_cast<int>(koef * (com.parameters[y_val] - unit_y));
	}
	look_angle = com.parameters[angle_val];
	if(!is_alive()) {
		state.make_dead();
		// mediator->delete_colleague(player_id, unit_id);
	}
	notify();
	return false;
}

bool Unit::interact(Command &com) {
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
	set_notify_need(true);
	notify();
	return is_alive();
}

size_t Unit::hash_self() const {
	size_t hash = 0;
	boost::hash_combine(hash, damage);
	boost::hash_combine(hash, radius);
	boost::hash_combine(hash, speed);
	boost::hash_combine(hash, look_angle);
	return hash;
}

bool operator==(const Unit &first, const Unit &second) {
	return first.hash_self() == second.hash_self();
}
