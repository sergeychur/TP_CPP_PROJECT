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

#include "parameter.hpp"

struct Command {
    public:
        Command(const std::string& _command_name, std::vector<Parameter>& _parameters);
        Command() = delete;
        Command(const Command&) = delete;
        Command(const Command&&) = delete;
        Command& operator=(const Command&) = delete;
        Command&& operator=(const Command&&) = delete;

        std::string command_name;
        std::vector<Parameter> parameters;
};

#endif //SERVER_COMMAND_HPP
