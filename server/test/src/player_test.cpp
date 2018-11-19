//
// Created by sergey on 29.10.18.
//

#include "player_tests.hpp"
#include "mock_base.hpp"
#include "mock_unit.hpp"


TEST(Player, creating_new) {
    MockBase base;
    // Player player(0, nullptr, &base);
    Player player(0);
    player.add_base(&base);
    std::vector<int> params = {0, 100, 0, 0, 30, 45, 20};
    Command command(0, 0, "create", params);
    std::vector<Command> commands;
    commands.push_back(command);
    player.act(commands);
    EXPECT_CALL(base, start_making(100, 0, 0, 30, 45, 20))
            .Times(1);
}

TEST(Player, moving_unit) {
    MockUnit unit;
    MockBase base;
    Player player(0);
    player.add_base(&base);
    player.add_unit(&unit);
    std::vector<int> params = {20, 30};
    Command command(0, 0, "move", params);
    std::vector<Command> commands;
    commands.push_back(command);
    player.act(commands);
    EXPECT_CALL(unit, act(command));
}

TEST(Player, kicking_other) {
    MockUnit unit;
    MockBase base;
    Player player(0);
    player.add_base(&base);
    player.add_unit(&unit);
    std::vector<int> params = {0, 0};   // player_id, unit_id
    Command command(0, 0, "kick", params);
    std::vector<Command> commands;
    commands.push_back(command);
    player.act(commands);
    EXPECT_CALL(unit, act(command));
}