cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(Boost 1.67.0 COMPONENTS serialization log system REQUIRED)
include_directories($Boost_INCLUDE_DIR)
add_library(Net src/NetObject.cpp include/NetObject.h src/Serializable.cpp include/Serializable.h src/AbstractClientNetObject.cpp include/AbstractClientNetObject.h src/AbstractServerNetObject.cpp include/AbstractServerNetObject.h src/ServerNetObject.cpp include/ServerNetObject.h src/ClientNetObject.cpp include/ClientNetObject.h include/DefaultAbstractFactory.h include/SubSock.h src/SubSock.cpp)
target_link_libraries(Net ${Boost_LIBRARIES} Threads::Threads)


#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(tests test/gtest.cpp)