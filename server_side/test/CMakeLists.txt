cmake_minimum_required(VERSION 3.12)
project(server_tests)

# -std=c++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(PROJECT_ROOT ../../)

set(GMOCK_DIR ${PROJECT_ROOT}/shared_files/googletest/googlemock/)

# Boost magic
set(BOOST_DIR ../../shared_files/boost_1_67_0)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../shared_files")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
endif (Boost_NO_SYSTEM_PATHS)
find_package(Boost COMPONENTS serialization system filesystem log REQUIRED)

# tests
add_subdirectory(${GMOCK_DIR} ${PROJECT_ROOT}/shared_files/gmock)

# include directories for project
include_directories("${PROJECT_ROOT}/server_side/server/game/include")
include_directories("include/")
include_directories(${PROJECT_ROOT}/shared_files/include)
include_directories(${PROJECT_ROOT}/Net/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(SYSTEM ${GMOCK_DIR}/include ${GMOCK_DIR}/gtest/include)

# add_subdirectory("${PROJECT_ROOT}/server_side/server/game" game_lib)

# defining the vars for lists of src
# set(SRC_LIST ./src/game.cpp ./src/map.cpp ./src/player.cpp ./src/update_maker.cpp ./src/base.cpp ./src/unit.cpp ./src/real_unit.cpp
 #       ../shared_files/src/command.cpp ../shared_files/src/update.cpp ../shared_files/src/initialiser.cpp src/manager_impl.cpp)
set(TEST_SRC ./src/map_tests.cpp ./src/base_tests.cpp ./src/unit_tests.cpp ./src/player_tests.cpp)

# lib for game
# add_library(game_lib STATIC ${SRC_LIST})

# tests executable
add_executable(tests  ${TEST_SRC} ./src/gtest.cpp)


# add_library(game SHARED IMPORTED)
link_directories("${PROJECT_ROOT}/server/game/libgame.so")
target_link_libraries(tests game)

# some things for GTest
find_package(GTest REQUIRED)
find_package(Threads)

# linking libs with executables
target_link_libraries(tests Threads::Threads)
# target_link_libraries(tests game)
target_link_libraries(tests gtest gtest_main pthread)
target_link_libraries(tests gmock gmock_main)

# linking boost
 if(Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(tests ${Boost_LIBRARIES})
    target_link_libraries(tests ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})

 endif()