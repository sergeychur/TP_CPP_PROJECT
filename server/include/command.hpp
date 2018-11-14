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
        Command(const int& unit_id, const std::string& _command_name, std::vector<int>& _parameters);
        Command() = delete;
        // Command(const Command&) = delete;
        // Command(const Command&&) = delete;
        // Command& operator=(const Command&) = delete;
        // Command&& operator=(const Command&&) = delete;

        // int player_id;
        int unit_id;
        std::string command_name;   // add_unit, move, kick etc.
        std::vector<int> parameters;    // args
};

bool operator== (const Command&, const Command&);

#endif //SERVER_COMMAND_HPP
