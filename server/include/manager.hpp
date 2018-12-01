//
// Created by sergey on 30.11.18.
//

#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>

#include "DefaultAbstractFactory.h"


enum manager_errors {
    ERR_READ = -2
};

class ManagerException : public std::exception {
    public:
        explicit ManagerException(const std::string& mes) : message(mes) {};
        std::string what() {return message;}
    private:
        std::string message;
};

class Manager {
    public:
        Manager();
        ~Manager();
    template <class T>
        inline void input(T* value, const std::string& greeting) {
            bool success = false;
            do {
                std::cout << greeting << std::endl;
                std::cin >> *value;
                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    success = true;
                }
            } while (!success);
        }
        void read_bases_from_file(std::vector<std::pair<int, int>>&, const size_t);
        std::map<std::string,DefaultAbstractFactory*> get_instance_map();
    private:
        void parse_file_for_bases(const boost::filesystem::path& file,
                std::vector<std::pair<int, int>>& base_vector,
                const size_t player_num);
        boost::filesystem::path get_file_path(const size_t player_num);

        std::map<std::string,DefaultAbstractFactory*> map;
};

#endif //SERVER_MANAGER_HPP
