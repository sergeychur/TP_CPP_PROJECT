//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_BASE_TESTS_HPP
#define SERVER_BASE_TESTS_HPP


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "base.hpp"
#include "mock_mediator.hpp"

class BaseTests : public ::testing::Test {
    public:
        BaseTests(): base(nullptr, 100, 5, 7, 0) {}
    protected:
        Base base;
        void SetUp() {}
        void TearDown() {}
};

#endif //SERVER_BASE_TESTS_HPP
