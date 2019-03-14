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
    MOCK_METHOD0(is_alive, bool());
	MOCK_METHOD0(die, void());
    MOCK_METHOD0(remove, void());
    MOCK_METHOD0(notify, void());
    MOCK_METHOD1(interact, bool(Command&));
    MOCK_METHOD1(add, void(std::shared_ptr<NewsTaker>));
    MOCK_METHOD1(add_act_handler, void(std::shared_ptr<AbstractHandler>&));
    MOCK_METHOD1(add_distrib_handler, void(std::shared_ptr<AbstractHandler>&));
};

#endif //SERVER_MOCK_UNIT_HPP
