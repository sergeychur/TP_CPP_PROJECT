//
// Created by sergey on 30.11.18.
//

//
// Created by sergey on 23.11.18.
//

#include "manager.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <sstream>
#include <fstream>
#include <chrono>
#include <random>


Manager::Manager() {
    map = {
            {"upd", new UpdateFactory()},
            {"com", new CommandFactory()},
            {"ini", new InitialiserFactory()}
    };
}

Manager::~Manager() {
    for(auto& line : map) {
        delete line.second;
    }
    map.clear();
}

boost::filesystem::path Manager::get_file_path(const size_t player_num) {
    boost::filesystem::path file_path("maps");
    std::stringstream folder;
    folder << player_num;
    file_path = file_path / folder.str();

    size_t file_num = std::distance(boost::filesystem::directory_iterator(file_path), boost::filesystem::directory_iterator{});
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);
    folder.str("");
    folder << generator() % file_num << ".xml";
    file_path = file_path / folder.str();
    return file_path;
}

void Manager::parse_file_for_bases(const boost::filesystem::path& file,
        std::vector<std::pair<int, int>>& base_vector, const size_t player_num) {
    boost::property_tree::ptree tree;
    boost::filesystem::current_path(file.parent_path());
    boost::property_tree::read_xml(file.filename().string(), tree);
    BOOST_FOREACH(auto const& node, tree.get_child("bases")) {
        base_vector.emplace_back(node.second.get<int>("base_x"),
                                     node.second.get<int>("base_y"));
    }
}

void Manager::read_bases_from_file(std::vector<std::pair<int, int>>& base_vector, const size_t player_num) {
    boost::filesystem::path file_name;
    try {
        file_name = get_file_path(player_num);
    } catch(const boost::filesystem::filesystem_error& e) {
        throw ManagerException(e.what());
    }
    try {
        parse_file_for_bases(file_name, base_vector, player_num);
    } catch(boost::property_tree::ptree_error& e) {
        throw ManagerException(e.what());
    } catch(boost::filesystem::filesystem_error& e) {
        throw ManagerException(e.what());
    }

}

std::map<std::string,DefaultAbstractFactory*> Manager::get_instance_map() {
    return map;
}
