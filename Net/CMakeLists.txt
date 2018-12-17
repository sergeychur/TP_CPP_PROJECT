cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost 1.67.0 COMPONENTS serialization system REQUIRED)
include_directories($Boost_INCLUDE_DIR)
include_directories(include)
add_library(Net src/ClientNetObject.cpp src/ClientNetObjectImpl.cpp src/SerializationOperation.cpp src/ServerNetObject.cpp src/ServerNetObjectImpl.cpp src/SubSock.cpp)
target_link_libraries(Net ${Boost_LIBRARIES} Threads::Threads)


#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(tests test/gtest.cpp)