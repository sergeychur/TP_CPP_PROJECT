//
// Created by sergey on 28.10.18.
//

#include "mock_news_taker.hpp"
#include "mock_mediator.hpp"

TEST(Unit, sending_to_news_taker) {
    MockMediator med;
    Unit unit(0, 0, 100, 0, 0, 20, 5, 30, 0, &med);
    MockNewsTaker updater;
    std::vector<int> params = {1, 5};
    const std::string line_to_pass = "move";
    Command order(0, 0, "move", params);
    unit.act(order);
    /*
     * UpdateLine(const size_t&_player_id, const size_t&_unit_id, const int& _new_HP, const int& _new_x, const int& _new_y,
            const int& _new_angle, const bool& _is_alive):
     */
    UpdateLine line(0, 0, 100, 1, 5, 78, true);    // check out the last parameter(angle), i think it is arctg(5) and the unit shouldn't move that fast, hehe
    EXPECT_CALL(updater, handle_event(line));
}

