cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 11)

#set(Boost_INCLUDE_DIR /home/alex/boost/boost_1_67_0/)
#set(Boost_LIBRARY_DIR /home/alex/boost/boost_1_67_0/lib/)
#set(BOOST_ROOT /usr/local/boost_1_67_0/)
#find_package(Boost 1.67.0 COMPONENTS REQUIRED system)
include_directories(/home/alex/boost/boost_1_67_0)
link_directories(/home/alex/boost/boost_1_67_0/stage/lib)

add_library(Net src/NetObject.cpp include/NetObject.h src/Serializable.cpp include/Serializable.h src/AbstractClientNetObject.cpp include/AbstractClientNetObject.h src/AbstractServerNetObject.cpp include/AbstractServerNetObject.h src/ServerNetObject.cpp include/ServerNetObject.h src/ClientNetObject.cpp include/ClientNetObject.h DefaultAbstractFactory.h)

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(tests test/gtest.cpp)