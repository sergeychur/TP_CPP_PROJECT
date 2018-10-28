cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")

include_directories("include/")

set(SRC_LIST src/game.cpp src/map.cpp src/player.cpp src/update_maker.cpp test/gtest.cpp)

add_library(game_lib STATIC ${SRC_LIST})

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(tests test/gtest.cpp test/map_tests.cpp test/base_tests.cpp test/unit_tests.cpp test/update_maker_tests.cpp test/player_test.cpp)

find_package( GTest REQUIRED )
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(tests ${GTEST_LIBRARIES})
target_link_libraries(tests game_lib)
target_link_libraries(tests Threads::Threads)