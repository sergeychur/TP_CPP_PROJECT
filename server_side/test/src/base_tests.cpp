//
// Created by sergey on 28.10.18.
//

#include "base.hpp"
#include "handler.hpp"

#include "mock_mediator.hpp"
#include "mock_news_taker.hpp"

TEST(Base, building_new_unit1) {
	auto mediator = std::make_shared<MockMediator>();
	Base base(mediator, 100, 0, 0, 0);
	const std::chrono::high_resolution_clock::duration duration_4_seconds = std::chrono::seconds(4);
	const double time = duration_4_seconds.count();
	auto test_news_taker = std::make_shared<MockNewsTaker>();
	base.add(test_news_taker);
	std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
	Command com(0, 1, "create_unit", params);
	base.start_making(com);
	std::shared_ptr<Unit> new_unit;
	if (base.is_ready_for_time(time)) {
		new_unit = std::dynamic_pointer_cast<Unit>(base.get_unit());
	}
	Unit new_real_unit(0, 1, 100, 0, 0, 78, 5, 23, 0, nullptr);
	EXPECT_EQ(*new_unit, new_real_unit);
	new_unit.reset();
	mediator.reset();
}

TEST(Base, building_new_unit2) {
	auto mediator = std::make_shared<MockMediator>();
	Base base(mediator, 100, 0, 0, 0);
	const std::chrono::high_resolution_clock::duration duration_0_seconds = std::chrono::seconds(0);
	const double time = duration_0_seconds.count();
	std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
	auto test_news_taker = std::make_shared<MockNewsTaker>();
	base.add(test_news_taker);
	Command com(0, 1, "create_unit", params);
	base.start_making(com);
	std::shared_ptr<Unit> new_unit;
	if (base.is_ready_for_time(time)) {
		new_unit = std::dynamic_pointer_cast<Unit>(base.get_unit());
	}
	ASSERT_EQ(new_unit.get(), nullptr);
	new_unit = std::dynamic_pointer_cast<Unit>(base.get_unit());
	new_unit.reset();
	mediator.reset();
}

TEST(Base, get_kicked1) {
	auto mediator = std::make_shared<MockMediator>();
	std::shared_ptr<Base> base = std::make_shared<Base>(mediator, 100, 0, 0, 0);
	auto upd_taker = std::make_shared<MockNewsTaker>();
	base->add(upd_taker);
	std::function<bool(Command &)> get_kicked_func =
			std::bind(&Base::get_kicked, base.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> kick_handler = std::make_shared<Handler<Base>>(base, "get_kicked",
																					get_kicked_func);
	base->add_act_handler(kick_handler);
	std::vector<int> params = {100, 5, 1, 1};
	const std::string line_to_pass = "get_kicked";
	Command com(0, 0, line_to_pass, params);
	base->interact(com);
	EXPECT_FALSE(base->is_alive());
	mediator.reset();
}

TEST(Base, get_kicked2) {
	auto mediator = std::make_shared<MockMediator>();
	std::shared_ptr<Base> base = std::make_shared<Base>(mediator, 100, 0, 0, 0);
	auto upd_taker = std::make_shared<MockNewsTaker>();
	base->add(upd_taker);
	std::function<bool(Command &)> get_kicked_func =
			std::bind(&Base::get_kicked, base.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> kick_handler = std::make_shared<Handler<Base>>(base, "get_kicked",
																					get_kicked_func);
	base->add_act_handler(kick_handler);
	std::vector<int> params = {10, 5, 10, 9};
	const std::string line_to_pass = "get_kicked";
	Command com(0, 0, line_to_pass, params);
	base->interact(com);
	EXPECT_TRUE(base->is_alive());
	mediator.reset();
}
