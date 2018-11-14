//
// Created by sergey on 19.10.18.
//

/*
    Main entity in game world, interacts with out, gets commands from net and applies them
*/

#ifndef SERVER_GAME_HPP
#define SERVER_GAME_HPP

#include <vector>

#include "map.hpp"
#include "player.hpp"
#include "update.hpp"
#include "command.hpp"
#include "update_maker.hpp"

class Game {
    private:
        Mediator* map;    // map of the world
        std::vector<Player> player_arr;     // the array of the players(the models of clients)
        NewsTaker* update_maker;       // this gets the updates from all the changing objects
        int stat;   // the status of the game, updating every iteration of the loop
        size_t player_num;

    public:
        explicit Game(const size_t& _player_num);
        ~Game();
        Game() = delete;
        Game(const Game&) = delete;
        Game(const Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(const Game&&) = delete;

        void add_player(const int& _x, const int& _y, const size_t& player_id);
        bool is_win() const {return stat != -1;}
        int act(std::vector<std::vector<Command>>&);
        Update* get_update();    // returns the update to send to clients

};

#endif //SERVER_GAME_HPP
