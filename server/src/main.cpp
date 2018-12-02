#include <iostream>
#include <fstream>
#include <climits>

#include "game.hpp"
#include "manager.hpp"

#include "ServerNetObject.h"

#include <memory>   // remove

int main(void) {
    size_t player_num = 0;
    Manager manager;
    manager.input(&player_num, "Enter the number of players");
    Game game(player_num);
    std::vector<std::pair<int, int>> bases;
    try {
        manager.read_bases_from_file(bases, player_num);
    } catch(ManagerException& e) {
        std::cout << e.what() << std::endl;
        return ERR_READ;
    }
    uint port = 0;
    manager.input(&port, "Enter the port to listen on");
    std::string ip("");
    manager.input(&ip, "Enter the ip to listen on");     // WTF, for what do we need to enter IP
    std::map<std::string, DefaultAbstractFactory*> map;
    map = manager.get_instance_map();      // fill it with factories, think how
    std::cout << "Success entering" << std::endl;
    ServerNetObject server(port, ip, player_num, map);
    server.work();
    std::cout << "Success" << std::endl;
    for(size_t i = 0; i < player_num; ++i) {
        try {
            game.add_player(bases[i], i);
        } catch(std::invalid_argument& e) {
            std::cerr << "Cannot add player, because of" << e.what() << std::endl;
            throw e;
        }
        Initialiser init(i, player_num, bases);
        server.send_to(&init, i);
    }
    size_t winner = player_num;
    while(!game.is_win()) {
        std::vector<std::unique_ptr<Serializable>> clients_data = server.receive();
        // std::vector<std::shared_ptr<Serializable>> clients_data;
        /*int i = 0;
        while(i < 2) {
            Command com;
            std::cout << "Enter next command" << std::endl;
            std::cin >> com;
            clients_data.push_back(std::make_shared<Command>(com));
            ++i;
        }
        std::cin.clear();*/
        try {
            winner = game.act(clients_data);
        }
        catch (std::exception& e) {
            std::cerr << "Can't act because of "<< e.what() << std::endl;
        }
        std::unique_ptr<Update> update;
        try {
            update = game.get_update();
        }
        catch(std::exception& e) {
            std::cerr << "Can't get update because of " << e.what() << std::endl;
        }
        if(update) {
            std::cout << "Update to send is:" << std::endl;
            std::cout << *(update) << std::endl;       // in order to test, remove
            server.send(update.get());      // change for std::move
        }
    }
    std::cout << "And the winner iiiiiiiis player nuuuuuuumberrrr " << winner << std::endl;
    // here should be sending the result to clients and destroying the connection
    return 0;
}