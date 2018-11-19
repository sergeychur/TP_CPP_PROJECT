//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_PLAYER_TESTS_HPP
#define SERVER_PLAYER_TESTS_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "player.hpp"


class PlayerTests : public ::testing::Test {
public:
    PlayerTests();
    ~PlayerTests() override;
protected:
    Player* player;
    void SetUp() {}
    void TearDown() {}
};
#endif //SERVER_PLAYER_TESTS_HPP
