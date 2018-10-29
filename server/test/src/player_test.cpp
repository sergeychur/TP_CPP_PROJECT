//
// Created by sergey on 29.10.18.
//

#include "player_tests.hpp"




PlayerTests::PlayerTests() {
    AbstractBase* base = new  MockBase();
    AbstractUnit* unit = new MockUnit();
    player = new Player(0, unit, base);
}

PlayerTests::~PlayerTests() {
    delete player;
}

TEST(Player, creating_new) {
    MockBase base;
    Player player(0, nullptr, &base);
    std::vector<int> params = {0, 100, 0, 0, 30, 45, 20};
    Command command(0, "create", params);
    std::vector<Command> commands;
    commands.push_back(command);
    player.act(commands);
    EXPECT_CALL(base, start_making(100, 0, 0, 30, 45, 20))
            .Times(1);
}

TEST(Player, moving_unit) {
    MockUnit unit;
    MockBase base;
    Player player(0, &unit, &base);
    std::vector<int> params = {20, 30};
    Command command(0, "move", params);
    std::vector<Command> commands;
    commands.push_back(command);
    player.act(commands);
    EXPECT_CALL(unit, act(command));
}

TEST(Player, kicking_other) {
    MockUnit unit;
    MockBase base;
    Player player(0, &unit, &base);
    std::vector<int> params = {0, 0};   // player_id, unit_id
    Command command(0, "kick", params);
    std::vector<Command> commands;
    commands.push_back(command);
    player.act(commands);
    EXPECT_CALL(unit, act(command));
}