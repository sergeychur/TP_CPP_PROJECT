//
// Created by sergey on 03.12.18.
//

#include "player.hpp"
#include "mock_base.hpp"
#include "mock_unit.hpp"

TEST(Player, call_base) {
	auto base = std::make_shared<MockBase>();
	Player player(0);
	player.add_base(base);
	std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
	ON_CALL(*base, is_alive())
			.WillByDefault(testing::Return(true));
	Command command(0, 0, "create_unit", params);
	EXPECT_CALL(*base, act(command));
	player.act(command);
}

TEST(Player, call_unit) {
	auto unit = std::make_shared<MockUnit>();
	Player player(0);
	auto base = std::make_shared<MockBase>();
	player.add_base(base);
	player.add_unit(unit);
	std::vector<int> params = {100, 0, 0, 0};
	ON_CALL(*unit, is_alive())
			.WillByDefault(testing::Return(true));
	Command command(0, 1, "check", params);
	EXPECT_CALL(*unit, act(command));
	player.act(command);
}
