cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-energy)

add_library(exhaustive-gc-energy SHARED
        src/energy.cpp)

target_include_directories(exhaustive-gc-energy PRIVATE
        include
        ${GEOC_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(exhaustive-gc-energy
        ${DGTAL_LIBRARIES})