#include <iostream>
#include <unordered_set>

#include "game.hpp"
#include "manager.hpp"
#include "input.hpp"
#include "initialiser.hpp"
#include "adapter.hpp"


int main() {
	size_t player_num = 0;
	Manager manager;
	input(&player_num, "Enter the number of players");
	Game game(player_num);
	std::vector<std::pair<int, int>> bases;
	try {
		manager.read_bases_from_file(bases, player_num);
	} catch (ManagerException &e) {
		std::cout << e.what() << std::endl;
		return ERR_READ;
	}
	uint port = 0;
	input(&port, "Enter the port to listen on");
	std::string ip;
	input(&ip, "Enter the ip to listen on");
	std::map<std::string, DefaultAbstractFactory *> map;
	map = manager.get_instance_map();
	std::cout << "Success entering" << std::endl;
	std::unique_ptr<Server> server = std::make_unique<Adapter>(port, ip, player_num, map);
	server->work();
	std::cout << "Success" << std::endl;
	for (size_t i = 0; i < player_num; ++i) {
		try {
			game.add_player(bases[i], i);
		} catch (std::invalid_argument &e) {
			std::cerr << "Cannot add player, because of" << e.what() << std::endl;
			throw e;
		}
		Initialiser init(i, player_num, bases);
		try {
			server->send_to(&init, i);
		} catch (std::exception &e) {
			std::cerr << "Cannot send cause of" << e.what() << std::endl;
			return ERR_SEND;
		}
	}
	size_t winner = player_num;
	while (!game.is_win()) {
		std::vector<Command> commands;
		do {
			commands = server->receive();
		} while (commands.empty());

		try {
			winner = game.act(commands);
		}
		catch (std::exception &e) {
			std::cerr << "Can't act because of " << e.what() << std::endl;
		}
		std::unique_ptr<Update> update;
		try {
			update = game.get_update();
		} catch (std::exception &e) {
			std::cerr << "Can't get update because of " << e.what() << std::endl;
		}
		if (update) {
			std::cout << "Update to send is:" << std::endl;
			std::cout << *(update) << std::endl;       // in order to test, remove

			try {
				server->send(update.get());
			} catch (std::exception &e) {
				std::cerr << "Cannot send, cause of " << e.what() << std::endl;
			}
		}
	}
	std::cout << "And the winner iiiiiiiis player nuuuuuuumberrrr " << winner << std::endl;
	return 0;
}
