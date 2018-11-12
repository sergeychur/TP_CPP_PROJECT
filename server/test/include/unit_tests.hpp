//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_UNIT_TESTS_HPP
#define SERVER_UNIT_TESTS_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "news_taker.hpp"
#include "unit.hpp"


class MockNewsTaker : public NewsTaker {
    public:
        MockNewsTaker() = default;
        MOCK_METHOD1(handle_event, void(UpdateLine&));
        MOCK_METHOD0(get_update, Update());
        MOCK_METHOD0(delete_update, void());
};

class MockMediator : public Mediator {
    public:
        MockMediator() = default;
        MOCK_METHOD3(add_colleague, void(Colleague*, const int&, const int&));
        MOCK_METHOD1(make_interaction, bool(std::vector<int>&));
};

#endif //SERVER_UNIT_TESTS_HPP
