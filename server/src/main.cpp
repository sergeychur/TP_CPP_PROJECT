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
        // here should be getting params from clients
        int x = 0;
        int y = 0;
        game.add_player(x, y, i);
    }
    int winner = -1;
    while(!game.is_win()) {
        std::vector<std::vector<Command>> clients_data;
        // here should be getting params from clients
        winner = game.act(clients_data);
        Update update = game.get_update();
        // here should be some sending to clients
    }
    std::cout << winner << std::endl;   // remove later
    // here should be sending the result to clients and destroying the connection
    return 0;
}