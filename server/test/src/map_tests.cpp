//
// Created by sergey on 28.10.18.
//

#include "map.hpp"
#include "map_tests.hpp"
#include "mock_colleague.hpp"

TEST_F(MapTests, makes_interaction) {
    MockColleague colleague(&map);
    std::vector<int> params = {10, 5, 10, 10};
    const std::string line_to_pass = "get_kicked";
    map.add_colleague(&colleague, 0, 0);
    map.make_interaction(0, 0, line_to_pass, params);
    EXPECT_CALL(colleague, interact(line_to_pass, params))
            .Times(1);
}

TEST_F(MapTests, makes_interaction_1) {
    MockColleague colleague(&map);
    std::vector<int> params = {10, 5, 10, 10};
    const std::string line_to_pass = "get_kicked";
    map.add_colleague((&colleague), 0, 0);
    map.make_interaction(0, 0, line_to_pass, params);
    EXPECT_CALL(colleague, interact(line_to_pass, params))
            .WillOnce(::testing::Return(true));
}

TEST_F(MapTests, makes_interaction_2) {
    MockColleague colleague(&map);
    std::vector<int> params = {10, 5, 10, 10};
    const std::string line_to_pass = "get_kicked";
    map.add_colleague((&colleague), 0, 0);
    map.make_interaction(1, 0, line_to_pass, params);
    EXPECT_CALL(colleague, interact(line_to_pass, params))
            .WillOnce(::testing::Return(false));
}