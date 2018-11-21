//
// Created by sergey on 16.11.18.
//

#ifndef SERVER_MOCK_BASE_HPP
#define SERVER_MOCK_BASE_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "abstract_base.hpp"



class MockBase : public AbstractBase {
public:
    MockBase() : AbstractBase(nullptr) {};
    MOCK_METHOD1(start_making, void(std::vector<int>&));
    MOCK_METHOD0(is_alive, bool());
    MOCK_METHOD0(is_ready, bool());
    MOCK_METHOD0(get_unit, Unit*());
    MOCK_METHOD2(interact, int(const std::string&, std::vector<int>&));

};

#endif //SERVER_MOCK_BASE_HPP
