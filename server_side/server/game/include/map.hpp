//
// Created by sergey on 19.10.18.
//

/*
 the mediator of the game, checking the legitimacy of the action and letting the units to interact
 */

#ifndef SERVER_MAP_HPP
#define SERVER_MAP_HPP

#include <vector>

#include "mediator.hpp"

class Map : public Mediator {
 public:
	Map() : Mediator() {}

	void add_colleague(const std::shared_ptr<Colleague> &, size_t player_id,
					   size_t unit_id) override;

	bool make_interaction(Command &) override;

	void delete_colleague(size_t, size_t) override;

	~Map() override;

 private:
	std::vector<std::vector<std::weak_ptr<Colleague>>> unit_matrix;
};

#endif        //  SERVER_MAP_HPP
