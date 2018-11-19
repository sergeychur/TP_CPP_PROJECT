cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 11)

add_library(Net NetObject.cpp NetObject.h Serializable.cpp Serializable.h AbstractClientNetObject.cpp AbstractClientNetObject.h AbstractServerNetObject.cpp AbstractServerNetObject.h ServerNetObject.cpp ServerNetObject.h ClientNetObject.cpp ClientNetObject.h)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests test/gtest.cpp)