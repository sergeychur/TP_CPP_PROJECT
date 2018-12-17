//
// Created by sergey on 15.12.18.
//

#ifndef SERVER_MANAGER_IMPL_HPP
#define SERVER_MANAGER_IMPL_HPP

#include <iostream>
#include <string>
#include <boost/filesystem/path.hpp>
#include <map>

#include "DefaultAbstractFactory.h"

class ManagerImpl {
 public:
	ManagerImpl();

	~ManagerImpl();

	void read_bases_from_file(std::vector<std::pair<int, int>> &, size_t);

	std::map<std::string, DefaultAbstractFactory *> get_instance_map();

 private:
	void parse_file_for_bases(const boost::filesystem::path &file,
							  std::vector<std::pair<int, int>> &base_vector,
							  size_t player_num);

	boost::filesystem::path get_file_path(size_t player_num);

	std::map<std::string, DefaultAbstractFactory *> map;
};

#endif        //  SERVER_MANAGER_IMPL_HPP
