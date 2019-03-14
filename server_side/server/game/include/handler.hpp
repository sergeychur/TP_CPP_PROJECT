//
// Created by sergey on 14.12.18.
//

#ifndef SERVER_HANDLER_HPP
#define SERVER_HANDLER_HPP

#include "abstract_handler.hpp"
#include "unit.hpp"

template<class T>
class Handler : public AbstractHandler {
 public:
	Handler(std::shared_ptr<T> _master, const std::string &_command_name,
			const std::function<bool(Command &)> &_callable) :
			unit(_master), command_name(_command_name),
			callable(_callable) {}

	bool handle(Command &command) override {
		return callable(command);
	}

	bool can_handle(const std::string &name) override {
		return name == command_name;
	}

 private:
	std::weak_ptr<T> unit;
	std::string command_name;
	std::function<bool(Command &)> callable;
};

#endif        //  SERVER_HANDLER_HPP
