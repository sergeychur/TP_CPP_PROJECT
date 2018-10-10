cmake_minimum_required(VERSION 3.9)
project(Net)

set(CMAKE_CXX_STANDARD 11)

add_library(Net NetObject.cpp NetObject.h ServerNetObject.cpp ServerNetObject.h ClientNetObject.cpp ClientNetObject.h)