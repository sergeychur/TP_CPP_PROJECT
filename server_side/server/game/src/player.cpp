//
// Created by sergey on 19.10.18.
//

#include <iostream>

#include "player.hpp"
#include "handler.hpp"
#include "base.hpp"

Player::~Player() {
	base.reset();
	for (auto &it : unit_arr) {
		it.reset();
	}
	unit_arr.clear();
}

size_t Player::act(Command &command) {
	if (!base->is_alive()) {
		--unit_num;
	} else if (base->is_ready()) {
		try {
			add_unit(base->get_unit());
		} catch (std::invalid_argument &e) {
			throw e;
		}
	}
	if (unit_arr.size() < command.unit_id) {
		throw std::invalid_argument("Wrong index");
	}
	for (size_t i = 0; i < unit_arr.size(); ++i) {
		if(unit_arr[i]) {
			if (!unit_arr[i]->is_alive()) {
				remove_unit(i);
			}
		}
	}
	if (unit_arr[command.unit_id] && id == command.player_id) {
		unit_arr[command.unit_id]->act(command);
	}
	if (!unit_num) {
		return DEAD;
	}
	return unit_num;
}

void Player::add_unit(std::shared_ptr<AbstractUnit> unit) {
	if (!unit) {
		throw std::invalid_argument("No unit to add");
	}
	unit_arr.push_back(unit);
	unit->notify();
	++unit_num;
}

void Player::remove_unit(const size_t id) {
	if (unit_arr[id]) {
		--unit_num;
		unit_arr[id]->die();
		unit_arr[id].reset();
	}
}

int Player::add_base(std::shared_ptr<NewsTaker> updater,
					 std::shared_ptr<Mediator> map, const int base_x, const int base_y) {
	if (base) {
		return ALREADY_EXISTS;
	}
	if (!map) {
		throw std::invalid_argument("No map given");
	}
	if (!updater) {
		throw std::invalid_argument("No updater given");
	}
	auto temp_base = std::make_shared<Base>(map, BASE_HP, base_x, base_y, id);
	base = temp_base;
	base->add(updater);
	if (!base) {
		return ERR_ALLOC;
	}

	std::function<bool(Command &)> get_kicked_func = std::bind(&Base::get_kicked, temp_base.get(),
															   std::placeholders::_1);
	std::shared_ptr<AbstractHandler> kick_handler = std::make_shared<Handler<Base>>(temp_base, "get_kicked",
																					get_kicked_func);
	base->add_act_handler(kick_handler);

	std::function<bool(Command &)> create_func =
			std::bind(&Base::start_making, temp_base.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> create_handler =
			std::make_shared<Handler<Base>>(temp_base, "create_unit", create_func);
	base->add_act_handler(create_handler);

	unit_arr.push_back(base);
	++unit_num;
	return 0;
}

void Player::add_base(std::shared_ptr<AbstractBase> _base) {
	if (!_base) {
		throw std::invalid_argument("No base given");
	}
	base = _base;
	unit_arr.push_back(base);
	base->notify();
	++unit_num;
}
