//
// Created by sergey on 20.11.18.
//

#include <iostream>
#include <map>

#include "real_unit.hpp"

bool RealUnit::get_kicked(Command &com) {
	enum indices {
		damage = 0,
		radius,
		x,
		y,
		params_number = 4
	};
	if (com.parameters.size() != params_number) {
		throw(std::invalid_argument("not enough params"));
	}

	if (((com.parameters[x] * com.parameters[x] - unit_x * unit_x) +
		 (com.parameters[y] * com.parameters[y] - unit_y * unit_y)) <=
		com.parameters[radius] * com.parameters[radius]) {
		HP -= com.parameters[damage];
		state.make_fighting();
		return true;
	}
	return false;
}
