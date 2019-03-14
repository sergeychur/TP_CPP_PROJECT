//
// Created by sergey on 16.12.18.
//

#ifndef SERVER_INPUT_HPP
#define SERVER_INPUT_HPP

#include <iostream>

template<class T>
void input(T *value, const std::string &greeting) {
	if (!value) {
		throw(std::invalid_argument("I dunno, where to enter"));
	}
	bool success = false;
	do {
		std::cout << greeting << std::endl;
		std::cin >> *value;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} else {
			success = true;
		}
	} while (!success);
}

#endif        //  SERVER_INPUT_HPP
