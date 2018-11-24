//
// Created by sergey on 12.11.18.
//

#ifndef SERVER_UTILS_HPP
#define SERVER_UTILS_HPP

#include <string>
#include <iostream>

template <class T>
void input(T* value, const std::string& greeting) {
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


#endif //SERVER_UTILS_HPP
