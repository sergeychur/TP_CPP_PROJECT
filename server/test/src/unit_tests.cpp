//
// Created by sergey on 28.10.18.
//

#include "mock_news_taker.hpp"
#include "mock_mediator.hpp"

/*MOCK_METHOD1(handle_event, void(UpdateLine&))
MOCK_METHOD0(get_update, Update*());
MOCK_METHOD0(delete_update, void());*/

/*void add(NewsTaker* news_taker) override;   // adds UpdateMaker
void remove() override;
void notify() override;
bool is_alive();
int act(Command& order) override;     // here the command is parsed*/

TEST(Unit, sending_to_news_taker) {
    MockMediator med;
    Unit unit(0, 0, 100, 0, 0, 20, 30, 0, &med);
    MockNewsTaker updater;
    // Command(const int& unit_id, const std::string& _command_name, std::vector<int>& _parameters);
    std::vector<int> params = {1, 5};
    Command order(0, 0, "move", params);
    unit.act(order);
    // UpdateLine(const int&_player_id, const int&_unit_id, const int& _new_HP, const int& _new_x, const int& _new_y,
    // const int& _new_angle):
    UpdateLine line(0, 0, 100, 1, 5, 1);    // check out the last parameter(angle), i think it is arctg(5) and the unit shouldn't move that fast, hehe
    EXPECT_CALL(updater, handle_event(line));
}

