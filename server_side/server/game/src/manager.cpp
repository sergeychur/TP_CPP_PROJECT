//
// Created by sergey on 30.11.18.
//

#include "manager.hpp"
#include "manager_impl.hpp"


Manager::Manager() : impl(std::make_unique<ManagerImpl>()) {}

Manager::~Manager() = default;

void Manager::read_bases_from_file(std::vector<std::pair<int, int>> &base_vector, const size_t player_num) {
	impl->read_bases_from_file(base_vector, player_num);
}

std::map<std::string, DefaultAbstractFactory *> Manager::get_instance_map() {
	return impl->get_instance_map();
}

