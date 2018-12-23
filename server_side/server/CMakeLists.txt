cmake_minimum_required(VERSION 3.12)
project(server)

# -std=c++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(PROJECT_ROOT ../../)

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
find_package(Boost COMPONENTS serialization system filesystem REQUIRED)

# include directories for project
include_directories("include/")
include_directories(${PROJECT_ROOT}/shared_files/include)

# Net from Alex
include_directories("${PROJECT_ROOT}/Net/include" ".${PROJECT_ROOT}/Net")
add_subdirectory("${PROJECT_ROOT}/Net" Net)


include_directories(game game/include)

add_subdirectory("game" )

add_subdirectory(xml_make)

# main executable
add_executable(${PROJECT_NAME}_main main.cpp game/src/adapter.cpp)

# linking libs with executables
target_link_libraries(${PROJECT_NAME}_main game)
target_link_libraries(${PROJECT_NAME}_main net_lib)


# linking boost
 if(Boost_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    add_definitions(${Boost_DEFINITIONS})

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_main ${Boost_LIBRARIES})
    target_link_libraries( ${PROJECT_NAME}_main ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY})

 endif()