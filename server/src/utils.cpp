//
// Created by sergey on 23.11.18.
//

#include "utils.hpp"

#include <boost/filesystem.hpp>
#include <sstream>
#include <chrono>
#include <random>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;

std::size_t count_files_in_directory(const std::string& str) {
    fs::path path(str);
    using fs::directory_iterator;
    return std::distance(directory_iterator(path), directory_iterator{});
}

std::string get_path(const size_t& pl_num) {
    std::stringstream ss;
    ss << "maps/" << pl_num << "/";
    size_t f_num = count_files_in_directory(ss.str());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);
    size_t rand_file = generator() % f_num;
    ss << rand_file << ".map";
    return ss.str();
}

// TODO(sergey): remake with boost
