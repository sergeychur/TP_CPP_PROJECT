//
// Created by sergey on 29.10.18.
//

#include "player_tests.hpp"
#include "mock_base.hpp"
#include "mock_unit.hpp"


TEST(Player, creating_new) {
    MockBase base;
    Player player(0);
    player.add_base(&base);
    std::vector<int> params = {0, 0, 100, 30, 5, 20, static_cast<int>(false)};
    const std::string line_to_pass = "create";
    Command command(0, 0, line_to_pass, params);
    player.act(command);
    std::vector<int> call_params = {0, 0, 100, 30, 5, 20, static_cast<int>(false)};
    EXPECT_CALL(base, start_making(call_params))
            .Times(1);
}

TEST(Player, moving_unit) {
    MockUnit unit;
    MockBase base;
    Player player(0);
    player.add_base(&base);
    player.add_unit(&unit);
    std::vector<int> params = {20, 30};
    const std::string line_to_pass = "move";
    Command command(0, 0, line_to_pass, params);
    player.act(command);
    EXPECT_CALL(unit, act(command));
}

TEST(Player, kicking_other) {
    MockUnit unit;
    MockBase base;
    Player player(0);
    player.add_base(&base);
    player.add_unit(&unit);
    std::vector<int> params = {0, 0};   // player_id, unit_id
    const std::string line_to_pass = "kick";
    Command command(0, 0, line_to_pass, params);
    player.act(command);
    EXPECT_CALL(unit, act(command));
}