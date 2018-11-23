cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
# -Wall -Wextra -Werror
set(GMOCK_DIR ./googletest/googlemock/)

set(BOOST_DIR ./boost_1_67_0)

# set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)

if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
endif (Boost_NO_SYSTEM_PATHS)

find_package(Boost COMPONENTS serialization REQUIRED)

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)


include_directories("test/include")
include_directories("include/")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(SYSTEM ${GMOCK_DIR}/include ${GMOCK_DIR}/gtest/include)





set(SRC_LIST src/game.cpp src/map.cpp src/player.cpp src/update_maker.cpp src/base.cpp src/unit.cpp src/real_unit.cpp src/utils.cpp)
set(TEST_SRC test/src/map_tests.cpp test/src/base_tests.cpp test/src/unit_tests.cpp)

add_library(game_lib STATIC ${SRC_LIST} src/command.cpp src/update.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(tests  ${TEST_SRC} test/src/gtest.cpp)

find_package(GTest REQUIRED)
find_package(Threads)

target_link_libraries(tests Threads::Threads)
target_link_libraries(${PROJECT_NAME} game_lib)
target_link_libraries(tests game_lib)
target_link_libraries(tests gtest gtest_main pthread)
target_link_libraries(tests gmock gmock_main)

if(Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    target_link_libraries( ${PROJECT_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()