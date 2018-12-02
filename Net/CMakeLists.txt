cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.67.0 COMPONENTS serialization system REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})
add_library(Net src/NetObject.cpp include/NetObject.h src/Serializable.cpp include/Serializable.h src/AbstractClientNetObject.cpp include/AbstractClientNetObject.h src/AbstractServerNetObject.cpp include/AbstractServerNetObject.h src/ServerNetObject.cpp include/ServerNetObject.h src/ClientNetObject.cpp include/ClientNetObject.h DefaultAbstractFactory.h)
target_link_libraries(Net ${Boost_LIBRARIES})
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(Net PUBLIC shared_files/include)
#add_executable(tests test/gtest.cpp)