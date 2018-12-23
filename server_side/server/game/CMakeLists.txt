cmake_minimum_required(VERSION 3.12)
project(game_lib)

# -std=c++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(PROJECT_ROOT ../../../)

# Boost magic
set(BOOST_DIR ${PROJECT_ROOT}/shared_files/boost_1_67_0)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "${PROJECT_ROOT}/shared_files")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
endif (Boost_NO_SYSTEM_PATHS)
find_package(Boost COMPONENTS serialization system filesystem log REQUIRED)

include_directories("include/")
include_directories(${PROJECT_ROOT}/shared_files/include)

set(SRC_LIST ./src/game.cpp ./src/map.cpp ./src/player.cpp ./src/update_maker.cpp ./src/base.cpp ./src/unit.cpp ./src/real_unit.cpp
        ./src/manager.cpp ./src/manager_impl.cpp
        ${PROJECT_ROOT}/shared_files/src/command.cpp ${PROJECT_ROOT}/shared_files/src/update.cpp ${PROJECT_ROOT}/shared_files/src/initialiser.cpp src/manager_impl.cpp)

add_library(game SHARED ${SRC_LIST})

if(Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(game ${Boost_LIBRARIES})
    target_link_libraries(game ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})

endif()