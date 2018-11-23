cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")

set(GMOCK_DIR ./googletest/googlemock/)

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)

include_directories("test/include")
include_directories("include/")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(SYSTEM ${GMOCK_DIR}/include ${GMOCK_DIR}/gtest/include)

set(SRC_LIST src/game.cpp src/map.cpp src/player.cpp src/update_maker.cpp src/base.cpp src/unit.cpp src/real_unit.cpp)
set(TEST_SRC test/src/map_tests.cpp test/src/base_tests.cpp test/src/unit_tests.cpp)

add_library(game_lib STATIC ${SRC_LIST} src/command.cpp src/update.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(tests  ${TEST_SRC} test/src/gtest.cpp)

find_package(GTest REQUIRED)
find_package(Threads)

target_link_libraries(tests Threads::Threads)
target_link_libraries(${PROJECT_NAME} game_lib)
target_link_libraries(tests game_lib)
target_link_libraries(tests gtest gtest_main pthread)
target_link_libraries(tests gmock gmock_main)