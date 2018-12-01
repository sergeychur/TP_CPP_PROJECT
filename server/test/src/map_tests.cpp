//
// Created by sergey on 28.10.18.
//

#include "map.hpp"
#include "map_tests.hpp"
#include "mock_colleague.hpp"

#include <iostream>

TEST_F(MapTests, makes_interaction) {
    std::shared_ptr<MockColleague> colleague = std::make_shared<MockColleague>(std::make_shared<Map>(map));
    std::vector<int> params = {10, 5, 10, 10};
    const std::string line_to_pass = "get_kicked";
    map.add_colleague(colleague, 0, 0);
    EXPECT_CALL(*colleague, interact(line_to_pass, params));
    map.make_interaction(0, 0, line_to_pass, params);
}

TEST_F(MapTests, makes_interaction_1) {
    std::shared_ptr<MockColleague> colleague = std::make_shared<MockColleague>(std::make_shared<Map>(map));
    std::vector<int> params = {10, 5, 10, 10};
    const std::string line_to_pass = "get_kicked";
    map.add_colleague(colleague, 0, 0);
    EXPECT_CALL(*colleague, interact(line_to_pass, params));
    map.make_interaction(0, 0, line_to_pass, params);
}

TEST_F(MapTests, makes_interaction_2) {
    std::vector<int> params = {10, 5, 10, 10};
    const std::string line_to_pass = "get_kicked";
    EXPECT_EQ(map.make_interaction(1, 0, line_to_pass, params), false);
}