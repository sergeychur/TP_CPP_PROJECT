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
    MockBase() : AbstractBase(nullptr, 100, 0, 0, 0) {};
    MOCK_METHOD6(start_making, void(const int&, const int&, const int&, const int&, const int&, const bool&));
    MOCK_METHOD0(is_alive, bool());
    MOCK_METHOD1(get_unit, Unit*(std::chrono::time_point<std::chrono::system_clock>&));
    MOCK_METHOD1(interact, int(std::vector<int>&));

};

#endif //SERVER_MOCK_BASE_HPP
