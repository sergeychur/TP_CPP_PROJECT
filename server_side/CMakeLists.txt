cmake_minimum_required(VERSION 3.12)
project(server_side)

# -std=c++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_subdirectory(server)

enable_testing()

add_subdirectory(test)