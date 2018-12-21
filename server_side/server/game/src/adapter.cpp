//
// Created by sergey on 17.12.18.
//

#include <iostream>
#include "adapter.hpp"

void Adapter::work() {
	server->work();
}

void Adapter::send_to(Serializable* data, int number) {
	server->send(data, number);
}

void Adapter::send(Serializable* data) {
	server->send(data);
}

std::vector<Command> Adapter::receive() {
//	std::vector<std::shared_ptr<Serializable>> clients_data = server->receive();
//	std::vector<Command> commands;
//	for(const auto& it : clients_data) {
//		std::shared_ptr<Command> command = std::dynamic_pointer_cast<Command>(it);
//		commands.push_back(*command);
//	}
	std::vector<std::shared_ptr<Serializable>> clients_data = server->receive();
	std::map<std::pair<int, int>, Command> checks;
	std::vector<Command> commands;
	for(auto it : clients_data) {
		std::shared_ptr<Command> command = std::dynamic_pointer_cast<Command>(it);
		if(command->command_name == "check") {
			if(checks.find({command->player_id, command->unit_id}) != checks.end()) {
				checks.erase({command->player_id, command->unit_id});
			}
			checks[{command->player_id, command->unit_id}] = *command;
		} else {
			if(command->command_name == "pop_command")
			{
				std::cout << "DAROVA" << std::endl;
			}
			commands.push_back(*command);
		}
	}
	for(auto it : checks) {
		commands.push_back(it.second);
	}
	return commands;
}
