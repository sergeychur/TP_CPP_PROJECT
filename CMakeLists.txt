cmake_minimum_required(VERSION 3.10)
project(TP_CPP_PROJECT)

set(CMAKE_CXX_STANDARD 11)

add_executable(TP_CPP_PROJECT main.cpp Game.cpp Game.h Level.cpp Level.h GameObject.cpp GameObject.h
        tinyXML/tinyxmlparser.cpp tinyXML/tinyxmlerror.cpp tinyXML/tinystr.cpp tinyXML/tinyxml.cpp tinyXML/tinystr.h
        tinyXML/tinyxml.h Unit.cpp Unit.h Player.cpp Player.h BaseBuilding.cpp BaseBuilding.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TP_CPP_PROJECT ${SFML_LIBRARIES})
endif()