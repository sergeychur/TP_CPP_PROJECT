//
// Created by sergey on 30.11.18.
//

#include <exception>
#include <iostream>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>


enum errors {
	ERR_ARGS = -1,
	ERR_INPUT = -2
};


int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: enter file name to create" << std::endl;
		return ERR_ARGS;
	}
	std::cout << "Enter the number of players" << std::endl;
	size_t player_num = 0;
	std::cin >> player_num;
	std::vector<std::pair<int, int>> bases;
	int i = 0;
	while (std::cin.good() && i < player_num) {
		std::cout << "Enter coord x" << std::endl;
		int x = 0;
		std::cin >> x;
		std::cout << "Enter coord y" << std::endl;
		int y = 0;
		std::cin >> y;
		bases.emplace_back(x, y);
		++i;
	}
	if (!std::cin.good()) {
		std::cerr << "something went wrong during input" << std::endl;
		return ERR_INPUT;
	}
	boost::property_tree::ptree tree;
	BOOST_FOREACH(const auto &elem, bases) {
					boost::property_tree::ptree cur_tree;

					cur_tree.put("base_x", elem.first);
					cur_tree.put("base_y", elem.second);
					tree.add_child("bases.base", cur_tree);
				}
	boost::property_tree::write_xml(argv[1], tree);
	return 0;
}
