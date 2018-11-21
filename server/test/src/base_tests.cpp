//
// Created by sergey on 28.10.18.
//

#include "base_tests.hpp"
#include "mock_mediator.hpp"

TEST_F(BaseTests, building_new_unit1) {
    const std::chrono::high_resolution_clock::duration duration_4_seconds = std::chrono::seconds(4);
    const double time = duration_4_seconds.count();
    /*enum indices {
        x = 0,
        y,
        HP,
        damage,
        radius,
        speed,
        if_start
    };*/
    std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
    base.start_making(params);
    Unit *new_unit = nullptr;
    if(base.is_ready_for_time(time)) {
         new_unit = base.get_unit();
    }
    Unit new_real_unit(0, 0, 100, 0, 0, 78, 5, 23, 0, nullptr);
    EXPECT_EQ(*new_unit, new_real_unit);
}

TEST_F(BaseTests, building_new_unit2) {
    const std::chrono::high_resolution_clock::duration duration_0_seconds = std::chrono::seconds(0);
    const double time = duration_0_seconds.count();
    std::vector<int> params = {0, 0, 100, 78, 5, 23, static_cast<int>(false)};
    base.start_making(params);
    Unit *new_unit = nullptr;
    if(base.is_ready_for_time(time)) {
        new_unit = base.get_unit();
    }
    ASSERT_EQ(new_unit, nullptr);
}

TEST_F(BaseTests, get_kicked1) {
    std::vector<int> params = {100, 5, 10, 9};
    const std::string line_to_pass = "get_kicked";
    base.interact(line_to_pass, params);
    ASSERT_TRUE(!base.is_alive());
}

TEST_F(BaseTests, get_kicked2) {
    std::vector<int> params = {10, 5, 10, 9};
    const std::string line_to_pass = "get_kicked";
    base.interact(line_to_pass, params);
    EXPECT_TRUE(base.is_alive());
}
