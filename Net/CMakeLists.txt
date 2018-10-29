cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 11)

add_library(Net NetObject.cpp NetObject.h ServerNetObject.cpp ServerNetObject.h Packet.cpp Packet.h)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests test/gtest.cpp test/packet_tests.cpp)