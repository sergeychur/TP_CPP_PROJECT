//
// Created by sergey on 28.10.18.
//

#include "mock_news_taker.hpp"
#include "mock_mediator.hpp"

TEST(Unit, sending_to_news_taker) {
    auto med = std::make_shared<MockMediator>();
    Unit unit(0, 0, 100, 0, 0, 20, 5, 30, 0, med);
    auto test_news_taker = std::make_shared<MockNewsTaker>();
    unit.add(test_news_taker);
    std::vector<int> params = {100, 0, 0, 0};
    const std::string line_to_pass = "check";
    Command order(0, 0, line_to_pass, params);
    UpdateLine line(0, 0, 100, 0, 0, 0, 0, true);
    EXPECT_CALL(*test_news_taker, handle_event(line));
    unit.act(order);
}

TEST(Unit, moving) {
    auto med = std::make_shared<MockMediator>();
    Unit unit(0, 0, 100, 0, 0, 20, 5, 30, 0, med);
    auto test_news_taker = std::make_shared<MockNewsTaker>();
    unit.add(test_news_taker);
    std::vector<int> move_vector = {10, 10};
    unit.move_for_time(move_vector, 1);
    std::vector<int> params = {100, 0, 0, 0};
    const std::string line_to_pass = "check";
    Command order(0, 0, line_to_pass, params);
    UpdateLine line(0, 0, 100, 0, 0, 0, 0, true);
    EXPECT_CALL(*test_news_taker, handle_event(line));
    unit.act(order);
}

TEST(Unit, kicking) {
    auto med = std::make_shared<MockMediator>();
    Unit unit(0, 0, 100, 0, 0, 20, 5, 30, 0, med);
    auto test_news_taker = std::make_shared<MockNewsTaker>();
    unit.add(test_news_taker);
    std::vector<int> kick_vector = {1, 1};
    unit.kick(kick_vector);
    std::vector<int> get_kicked_vector = {20, 5, 0, 0};
    std::string action_string("get_kicked");
    EXPECT_CALL(*med, make_interaction(1, 1, action_string, get_kicked_vector));
}

