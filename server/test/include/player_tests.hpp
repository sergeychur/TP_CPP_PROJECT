//
// Created by sergey on 29.10.18.
//

#ifndef SERVER_PLAYER_TESTS_HPP
#define SERVER_PLAYER_TESTS_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "player.hpp"

/*
    virtual void add(NewsTaker* news_taker) = 0;    // add somebody, who this should notify
        virtual void remove() = 0;      // remove observing smth
        virtual void notify() = 0;      // notify observing smth

*/

class MockUnit : public AbstractUnit {
public:
    MockUnit() : AbstractUnit(nullptr){};
    MOCK_METHOD1(act, int(Command&));
    MOCK_METHOD0(remove, void());
    MOCK_METHOD0(notify, void());
    MOCK_METHOD1(interact, int(std::vector<int>&));
    MOCK_METHOD1(add, void(NewsTaker*));
};

class MockBase : public AbstractBase {
    public:
        MockBase() : AbstractBase(nullptr, 100, 0, 0, 0) {};
        MOCK_METHOD6(start_making, void(const int&, const int&, const int&, const int&, const int&, const bool&));
        MOCK_METHOD0(is_alive, bool());
        MOCK_METHOD1(get_unit, Unit*(std::chrono::time_point<std::chrono::system_clock>&));
        MOCK_METHOD1(interact, int(std::vector<int>&));

};

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
