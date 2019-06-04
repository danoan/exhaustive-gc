cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-utils)

add_library(exhaustive-gc-utils SHARED
        src/timer.cpp)

target_include_directories(exhaustive-gc-utils PRIVATE
        include
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(exhaustive-gc-utils
        -lboost_system
        -lboost_filesystem)
