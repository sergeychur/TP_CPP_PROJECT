#include <iostream>
#include <climits>

#include "game.hpp"
#include "utils.hpp"

int main(void) {
    size_t player_num = 0;
    std::string greeting("Enter the number of players");
    input(&player_num, greeting);
    // here should be installing the connection with clients
    Game game(player_num);
    for(size_t i = 0; i < player_num; ++i) {
        int x = 0;
        int y = 0;
        // here should be getting params from clients
        try {
            game.add_player(x, y, i);
        } catch(std::invalid_argument& e) {
            std::cerr << "Cannot add player, because of" << e.what() << std::endl;
            return ERR_ADD;
        }
    }
    size_t winner = player_num;
    while(!game.is_win()) {
        std::vector<Command> clients_data;
        // here should be getting params from clients
        try {
            winner = game.act(clients_data);
        }
        catch (std::exception& e) {
            std::cerr << "Can't act because of "<< e.what() << std::endl;
        }
        Update update;
        try {
            update = game.get_update();
        }
        catch(std::invalid_argument& e) {
            std::cerr << "Can't get update because of " << e.what() << std::endl;
        }
        // here should be some sending to clients
    }
    std::cout << winner << std::endl;
    // here should be sending the result to clients and destroying the connection
    return 0;
}