//
// Created by sergey on 28.10.18.
//

#include "map.hpp"
#include "map_tests.hpp"
#include "mock_colleague.hpp"

TEST_F(MapTests, makes_interaction) {
    MockColleague colleague(&map);
    std::vector<int> params;
    params = {0, 0, -10};
    map.add_colleague(&colleague, 0, 0);
    map.make_interaction(params);
    EXPECT_CALL(colleague, interact(params))
            .Times(1);
}

TEST_F(MapTests, makes_interaction_1) {
    MockColleague colleague(&map);
    std::vector<int> params;
    params = {0, 0, -10};
    map.add_colleague((&colleague), 0, 0);
    map.make_interaction(params);
    EXPECT_CALL(colleague, interact(params))
            .WillOnce(::testing::Return(true));
}

TEST_F(MapTests, makes_interaction_2) {
    MockColleague colleague(&map);
    std::vector<int> params;
    params = {1, 0, -10};
    map.add_colleague((&colleague), 0, 0);
    map.make_interaction(params);
    EXPECT_CALL(colleague, interact(params))
            .WillOnce(::testing::Return(false));
}