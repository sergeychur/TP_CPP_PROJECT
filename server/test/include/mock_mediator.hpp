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
    ~MockMediator() = default;
    MOCK_METHOD3(add_colleague, void(Colleague*, const size_t, const size_t));
    MOCK_METHOD4(make_interaction, bool(const size_t, const size_t, const std::string&, std::vector<int>&));
};

#endif //SERVER_MOCK_MEDIATOR_HPP
