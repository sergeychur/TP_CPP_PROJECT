//
// Created by sergey on 28.10.18.
//

#include "base_tests.hpp"
#include "mock_mediator.hpp"

TEST_F(BaseTests, building_new_unit1) {
    const std::chrono::high_resolution_clock::duration duration_4_seconds = std::chrono::seconds(4);
    std::chrono::time_point<std::chrono::high_resolution_clock> time_point_4_seconds(duration_4_seconds);
    base.start_making(0, 0, 100, 78, 23, true); // x y hp damage speed
    Unit* new_unit = base.get_unit(time_point_4_seconds);
    Unit new_real_unit(0, 0, 100, 0, 0, 78, 23, 0, nullptr);
    EXPECT_EQ(*new_unit, new_real_unit);
}

TEST_F(BaseTests, building_new_unit2) {
    const std::chrono::high_resolution_clock::duration duration_0_seconds = std::chrono::seconds(0);
    std::chrono::time_point<std::chrono::high_resolution_clock> time_point_0_seconds(duration_0_seconds);
    base.start_making(0, 0, 100, 78, 23, false); // x y hp damage speed
    Unit* new_unit = base.get_unit(time_point_0_seconds);
    ASSERT_EQ(new_unit, nullptr);
}

TEST_F(BaseTests, get_kicked1) {
    std::vector<int> params;
    params.push_back(-100);
    base.interact(params);
    ASSERT_TRUE(!base.is_alive());
}

TEST_F(BaseTests, get_kicked2) {
    std::vector<int> params;
    params.push_back(-10);
    base.interact(params);
    EXPECT_TRUE(base.is_alive());
}
