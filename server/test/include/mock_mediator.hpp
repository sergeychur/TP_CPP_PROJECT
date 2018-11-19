//
// Created by sergey on 16.11.18.
//

#ifndef SERVER_MOCK_MEDIATOR_HPP
#define SERVER_MOCK_MEDIATOR_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mediator.hpp"

class MockMediator : public Mediator {
public:
    MockMediator() = default;
    MOCK_METHOD3(add_colleague, void(Colleague*, const int&, const int&));
    MOCK_METHOD1(make_interaction, bool(std::vector<int>&));
};

#endif //SERVER_MOCK_MEDIATOR_HPP
