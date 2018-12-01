//
// Created by sergey on 16.11.18.
//

#ifndef SERVER_MOCK_UNIT_HPP
#define SERVER_MOCK_UNIT_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "abstract_unit.hpp"

class MockUnit : public AbstractUnit {
public:
    MockUnit() : AbstractUnit(nullptr){};
    ~MockUnit() override = default;
    MOCK_METHOD1(act, bool(Command&));
    MOCK_METHOD0(remove, void());
    MOCK_METHOD0(notify, void());
    MOCK_METHOD2(interact, void(const std::string&, std::vector<int>&));
    MOCK_METHOD1(add, void(std::shared_ptr<NewsTaker>));
};

#endif //SERVER_MOCK_UNIT_HPP
