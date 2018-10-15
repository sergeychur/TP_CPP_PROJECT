cmake_minimum_required(VERSION 3.2)
project(TP_CPP_PROJECT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(TP_CPP_PROJECT main.cpp Game.cpp Game.h MapObject.cpp MapObject.h Level.cpp Level.h XML/tinyxml.cpp XML/tinyxml.h
        XML/tinystr.h XML/tinystr.cpp XML/tinyxmlerror.cpp XML/tinyxmlparser.cpp )

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TP_CPP_PROJECT ${SFML_LIBRARIES})
endif()