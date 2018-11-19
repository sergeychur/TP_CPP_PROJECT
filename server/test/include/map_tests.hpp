//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_MAP_TESTS_HPP
#define SERVER_MAP_TESTS_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "map.hpp"



class MapTests : public ::testing::Test {
public:
    MapTests() = default; // add when map exists
protected:
    Map map;

    void SetUp() final {}
    void TearDown() final {}
};

#endif //SERVER_MAP_TESTS_HPP
