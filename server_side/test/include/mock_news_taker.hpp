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
        ~MockNewsTaker() override = default;
        MOCK_METHOD1(handle_event, void(const UpdateLine&));
        MOCK_METHOD0(get_update, std::unique_ptr<Update>());
};


#endif //SERVER_UNIT_TESTS_HPP
