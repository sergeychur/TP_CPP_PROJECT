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
    MOCK_METHOD3(add_colleague, void(const std::shared_ptr<Colleague>&, const size_t, const size_t));
    MOCK_METHOD1(make_interaction, bool(Command&));
	MOCK_METHOD2(delete_colleague, void(size_t, size_t));
};

#endif //SERVER_MOCK_MEDIATOR_HPP
