//
// Created by sergey on 30.11.18.
//

#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <string>
#include <vector>
#include <map>


#include "DefaultAbstractFactory.h"


enum manager_errors {
	ERR_READ = -2,
	ERR_SEND = -3
};

class ManagerException : public std::exception {
 public:
	explicit ManagerException(const std::string &mes) : message(mes) {}

	std::string what() { return message; }

 private:
	std::string message;
};

class ManagerImpl;

class Manager {
 public:
	Manager();

	~Manager();

	void read_bases_from_file(std::vector<std::pair<int, int>> &, const size_t);

	std::map<std::string, DefaultAbstractFactory *> get_instance_map();

 private:
	std::unique_ptr<ManagerImpl> impl;
};

#endif        //  SERVER_MANAGER_HPP
