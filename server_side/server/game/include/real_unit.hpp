//
// Created by sergey on 28.10.18.
//

/*
    the part of a unit, that has coordinates
    from this base and unit derived
*/

#ifndef SERVER_REAL_UNIT_HPP
#define SERVER_REAL_UNIT_HPP

#include <cstddef>
#include <vector>
#include <string>


#include "command.hpp"
#include "state.hpp"

class RealUnit {
 public:
	RealUnit(const size_t _player_id, const size_t _unit_id, const int _HP, const int _unit_x,
			 const int _unit_y) : player_id(_player_id), unit_id(_unit_id), HP(_HP),
								  unit_x(_unit_x), unit_y(_unit_y), state() {}

	virtual ~RealUnit() = default;

	bool get_kicked(Command &);

 protected:
	State state;
	size_t player_id;
	size_t unit_id;
	int HP;
	int unit_x;
	int unit_y;

	constexpr static double allowed_linear_delta = 50;
};

#endif        //  SERVER_REAL_UNIT_HPP
