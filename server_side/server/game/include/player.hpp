//
// Created by sergey on 19.10.18.
//

/*
    the entity of player, modelling the client
*/

#ifndef SERVER_PLAYER_HPP
#define SERVER_PLAYER_HPP

#include <vector>

#include "abstract_unit.hpp"
#include "command.hpp"
#include "abstract_base.hpp"

enum player_constants {
	DEAD = -3,
	STILL_ACT = 0,
	SIMPLE = 2,
	BASE_HP = 100,
	ALREADY_EXISTS = -1,
	ERR_ALLOC = -2
};

class Player {
 private:
	size_t id;
	std::vector<std::shared_ptr<AbstractUnit>> unit_arr;     // the array of player's units
	void remove_unit(size_t id);        // removes unit by id when it is dead
	std::shared_ptr<AbstractBase> base;
	size_t unit_num;

 public:
	explicit Player(const size_t player_id) : id(player_id),
											  base(nullptr), unit_num(0) {}

	size_t act(Command &);

	int add_base(std::shared_ptr<NewsTaker> updater, std::shared_ptr<Mediator> med, int base_x, int base_y);

	void add_base(std::shared_ptr<AbstractBase>);

	void add_unit(std::shared_ptr<AbstractUnit>);    // adds new unit after it is made

	~Player();
};

#endif        //  SERVER_PLAYER_HPP
