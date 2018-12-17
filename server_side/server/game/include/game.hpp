//
// Created by sergey on 19.10.18.
//

/*
    Main entity in game world, interacts with out, gets commands from net and applies them
*/

#ifndef SERVER_GAME_HPP
#define SERVER_GAME_HPP

#include <vector>

#include "mediator.hpp"
#include "player.hpp"
#include "update.hpp"
#include "command.hpp"
#include "update_maker.hpp"

enum game_errors {
	ERR_ADD = -1
};

class Game {
 private:
	std::shared_ptr<Mediator> map;
	std::vector<std::unique_ptr<Player>> player_arr;     // the array of the players(the models of clients)
	std::shared_ptr<NewsTaker> update_maker;       // this gets the updates from all the changing objects
	size_t player_num;
	std::vector<int> avaliability;

 public:
	explicit Game(size_t _player_num);

	~Game();

	Game() = delete;

	Game(const Game &) = delete;

	Game(const Game &&) = delete;

	Game &operator=(const Game &) = delete;

	Game &operator=(const Game &&) = delete;

	void add_player(const std::pair<int, int> &base_coords, size_t player_id);

	bool is_win() const { return player_num <= 1; }

	size_t act(std::vector<Command> &);

	std::unique_ptr<Update> get_update();    // returns the update to send to clients
};

#endif        //  SERVER_GAME_HPP
