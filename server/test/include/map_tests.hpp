//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_MAP_TESTS_HPP
#define SERVER_MAP_TESTS_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "map.hpp"

class MockColleague : public Colleague {
    public:
        explicit MockColleague(Mediator* mediator1) : Colleague(mediator1) {}
        MOCK_METHOD1(interact, int(std::vector<int>&));
};

class MapTests : public ::testing::Test {
public:
    MapTests(): map("some_path") {} // add when map exists
protected:
    Map map;

    void SetUp() final {}
    void TearDown() final {}
};

#endif //SERVER_MAP_TESTS_HPP
