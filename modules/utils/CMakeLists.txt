cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-utils)

add_library(exhaustive-gc-utils SHARED
        src/timer.cpp
        src/digital.cpp)

target_include_directories(exhaustive-gc-utils PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(exhaustive-gc-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES})
