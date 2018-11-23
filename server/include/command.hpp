//
// Created by sergey on 19.10.18.
//

/*
    The command, sent by client to server
 */

#ifndef SERVER_COMMAND_HPP
#define SERVER_COMMAND_HPP

#include <string>
#include <vector>


struct Command {
    public:
        Command(const size_t _player_id, const size_t _unit_id,
                const std::string& _command_name, std::vector<int>& _parameters) :
                player_id(_player_id),
                unit_id(_unit_id), command_name(_command_name), parameters(_parameters) {};
        Command() = delete;
        // Command(const Command&) = delete;
        // Command(const Command&&) = delete;
        // Command& operator=(const Command&) = delete;
        // Command&& operator=(const Command&&) = delete;

        size_t player_id;
        size_t unit_id;
        std::string command_name;   // add_unit, move, kick etc.
        std::vector<int> parameters;    // args
};

bool operator== (const Command& first, const Command& second);

#endif //SERVER_COMMAND_HPP
