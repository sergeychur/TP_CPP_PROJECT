cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.65.0 REQUIRED)

add_library(Net src/NetObject.cpp include/NetObject.h src/Serializable.cpp include/Serializable.h src/AbstractClientNetObject.cpp include/AbstractClientNetObject.h src/AbstractServerNetObject.cpp include/AbstractServerNetObject.h src/ServerNetObject.cpp include/ServerNetObject.h src/ClientNetObject.cpp include/ClientNetObject.h)

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(tests test/gtest.cpp)