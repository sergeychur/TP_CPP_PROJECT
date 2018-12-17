//
// Created by sergey on 16.11.18.
//

#ifndef SERVER_MOCK_COLLEAGUE_HPP
#define SERVER_MOCK_COLLEAGUE_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mediator.hpp"

class MockColleague : public Colleague {
public:
    explicit MockColleague(std::shared_ptr<Mediator> mediator1) : Colleague(mediator1) {}
    ~MockColleague() override = default;
    MOCK_METHOD1(interact, bool(Command&));
    MOCK_METHOD0(die, void());
};

#endif //SERVER_MOCK_COLLEAGUE_HPP
