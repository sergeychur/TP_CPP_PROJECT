cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")

include_directories("include/")

set(SRC_LIST src/main.cpp src/game.cpp src/map.cpp src/player.cpp src/update_maker.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})