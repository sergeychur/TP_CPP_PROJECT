//
// Created by sergey on 03.12.18.
//

#ifndef SERVER_MANAGER_TESTS_HPP
#define SERVER_MANAGER_TESTS_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "manager.hpp"


class ManagerTests : public ::testing::Test {
public:
    ManagerTests() = default; // add when map exists
protected:
    Manager manager;

    void SetUp() final {}
    void TearDown() final {}
};

#endif //SERVER_MANAGER_TESTS_HPP
