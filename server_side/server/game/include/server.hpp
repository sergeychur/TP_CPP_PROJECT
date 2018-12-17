//
// Created by sergey on 17.12.18.
//

#ifndef SERVER_SIDE_SERVER_HPP
#define SERVER_SIDE_SERVER_HPP

#include <vector>

#include "Serializable.h"
#include "command.hpp"

class Server {
 public:
	virtual ~Server() = default;

	virtual void work() = 0;

	virtual void send_to(Serializable *, int) = 0;

	virtual void send(Serializable *) = 0;

	virtual std::vector<Command> receive() = 0;
};

#endif 		//  SERVER_SIDE_SERVER_HPP
