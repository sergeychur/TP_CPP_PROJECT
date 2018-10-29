cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")

include_directories("include/")

set(SRC_LIST src/game.cpp src/map.cpp src/player.cpp src/update_maker.cpp)

set(TEST_SRC test/src/map_tests.cpp test/src/base_tests.cpp test/src/unit_tests.cpp test/src/update_maker_tests.cpp test/src/player_test.cpp)

add_library(game_lib STATIC ${SRC_LIST})
add_library(test_lib STATIC ${TEST_SRC})

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(tests test/src/gtest.cpp)

find_package( GTest REQUIRED )
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories("test/include")

target_link_libraries(tests ${GTEST_LIBRARIES})
target_link_libraries(tests game_lib)
target_link_libraries(tests test_lib)
target_link_libraries(tests Threads::Threads)