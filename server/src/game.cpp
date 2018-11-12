//
// Created by sergey on 19.10.18.
//

#include "game.hpp"

Game::Game(const size_t& _player_num) : stat(-1), player_num(_player_num) {
    std::cout << player_num << std::endl;      // remove later
    /*
     *         Mediator* map;    // map of the world
        std::vector<Player*> player_arr;     // the array of the players(the models of clients)
        NewsTaker* update_maker;       // this gets the updates from all the changing objects
        int stat;   // the status of the game, updating every iteration of the loop
        size_t player_num;
     */
    update_maker = new UpdateMaker();
    map =  new Map();
}

Game::~Game() {
    std::cout << "destructor" << std::endl;
}

void Game::add_player(const int& _x, const int& _y, const size_t& player_id) {
    std::cout << "added player number " <<  player_id << " with base coordinates " << _x << " " << _y << std::endl;
}

int Game::act(std::vector<std::vector<Command>> commands_arr) {
    for(size_t i = 0; i < commands_arr.size() && stat == STILL_ACT; ++i) {
        stat = player_arr[i]->act(commands_arr[i]);
    }
    return stat;
}

Update Game::get_update() {
    return update_maker->get_update();   // check later

}

