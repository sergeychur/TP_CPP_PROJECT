//
// Created by sergey on 28.10.18.
//

#include "handler.hpp"
#include "mock_news_taker.hpp"
#include "mock_mediator.hpp"

TEST(Unit, sending_to_news_taker) {
	auto med = std::make_shared<MockMediator>();
	std::shared_ptr<Unit> unit = std::make_shared<Unit>(0, 0, 100, 0, 0, 20, 5, 30, 0, med);
	std::function<bool(Command &)> check_func =
			std::bind(&Unit::correct_state, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> check_handler = std::make_shared<Handler<Unit>>(unit, "check", check_func);
	unit->add_distrib_handler(check_handler);
	std::function<bool(Command &)> move_func = std::bind(&Unit::move, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> motion_handler = std::make_shared<Handler<Unit>>(unit, "move", move_func);
	unit->add_act_handler(motion_handler);
	auto test_news_taker = std::make_shared<MockNewsTaker>();
	unit->add(test_news_taker);
	std::vector<int> params = {100, 0, 0, 0};
	const std::string line_to_pass = "check";
	Command order(0, 0, line_to_pass, params);
	UpdateLine line(0, 0, 100, 0, 0, 0, 0, true);
	EXPECT_CALL(*test_news_taker, handle_event(line));
	unit->act(order);
}

TEST(Unit, moving) {
	auto med = std::make_shared<MockMediator>();
	std::shared_ptr<Unit> unit = std::make_shared<Unit>(0, 0, 100, 0, 0, 20, 5, 30, 0, med);
	std::function<bool(Command &)> check_func =
			std::bind(&Unit::correct_state, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> check_handler = std::make_shared<Handler<Unit>>(unit, "check", check_func);
	unit->add_distrib_handler(check_handler);
	std::function<bool(Command &)> move_func = std::bind(&Unit::move, unit.get(), std::placeholders::_1);
	std::shared_ptr<AbstractHandler> motion_handler = std::make_shared<Handler<Unit>>(unit, "move", move_func);
	unit->add_act_handler(motion_handler);
	auto test_news_taker = std::make_shared<MockNewsTaker>();
	unit->add(test_news_taker);
	std::vector<int> move_vector = {10, 10};
	unit->move_for_time(move_vector, 1);
	std::vector<int> params = {100, 0, 0, 0};
	const std::string line_to_pass = "check";
	Command order(0, 0, line_to_pass, params);
	UpdateLine line(0, 0, 100, 0, 0, 0, 0, true);
	EXPECT_CALL(*test_news_taker, handle_event(line));
	unit->act(order);
}
