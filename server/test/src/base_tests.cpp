//
// Created by sergey on 28.10.18.
//

#include "base.hpp"
#include "mock_mediator.hpp"
#include "mock_news_taker.hpp"

TEST(Base, building_new_unit1) {
    auto* mediator = new MockMediator();
    Base base(mediator, 100, 0, 0, 0);
    const std::chrono::high_resolution_clock::duration duration_4_seconds = std::chrono::seconds(4);
    const double time = duration_4_seconds.count();
    MockNewsTaker test_news_taker;
    base.add(&test_news_taker);
    std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
    base.start_making(params);
    Unit *new_unit = nullptr;
    if(base.is_ready_for_time(time)) {
         new_unit = base.get_unit();
    }
    Unit new_real_unit(0, 0, 100, 0, 0, 78, 5, 23, 0, nullptr);
    EXPECT_EQ(*new_unit, new_real_unit);
    delete new_unit;
    delete mediator;
}

TEST(Base, building_new_unit2) {
    auto* mediator = new MockMediator();
    Base base(mediator, 100, 0, 0, 0);
    const std::chrono::high_resolution_clock::duration duration_0_seconds = std::chrono::seconds(0);
    const double time = duration_0_seconds.count();
    std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
    MockNewsTaker test_news_taker;
    base.add(&test_news_taker);
    base.start_making(params);
    Unit *new_unit = nullptr;
    if(base.is_ready_for_time(time)) {
        new_unit = base.get_unit();
    }
    ASSERT_EQ(new_unit, nullptr);
    new_unit = base.get_unit();
    delete new_unit;
    delete mediator;
}

TEST(Base, get_kicked1) {
    auto* mediator = new MockMediator();
    Base base(mediator, 100, 0, 0, 0);
    std::vector<int> params = {100, 5, 1, 1};
    const std::string line_to_pass = "get_kicked";
    base.interact(line_to_pass, params);
    EXPECT_FALSE(base.is_alive());
    delete mediator;
}

TEST(Base, get_kicked2) {
    auto* mediator = new MockMediator();
    Base base(mediator, 100, 0, 0, 0);
    std::vector<int> params = {10, 5, 10, 9};
    const std::string line_to_pass = "get_kicked";
    base.interact(line_to_pass, params);
    EXPECT_TRUE(base.is_alive());
    delete mediator;
}
