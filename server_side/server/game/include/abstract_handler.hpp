//
// Created by sergey on 13.12.18.
//

#ifndef SERVER_ABSTRACT_HANDLER_HPP
#define SERVER_ABSTRACT_HANDLER_HPP

#include "command.hpp"
#include "string"

class AbstractHandler {
 public:
	virtual bool handle(Command &command) = 0;

	virtual bool can_handle(const std::string &command_name) = 0;
};

#endif        //  SERVER_ABSTRACT_HANDLER_HPP
