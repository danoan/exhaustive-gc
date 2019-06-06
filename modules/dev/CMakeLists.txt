cmake_minimum_required(VERSION 3.2)
project(neighbor-subgraph)

add_executable(neighbor-subgraph
        main.cpp)

target_include_directories(neighbor-subgraph PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS}
        ${DIPACUS_INCLUDE_DIRS})

target_link_libraries(neighbor-subgraph
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES})