cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-app-flow)

add_executable(exhaustive-gc-app-flow
        flow.cpp)

add_dependencies(exhaustive-gc-app-flow exhaustive-gc-api exhaustive-gc-base exhaustive-gc-utils)

target_include_directories(exhaustive-gc-app-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BTOOLS_INCLUDE_DIRS}
)

target_link_libraries(exhaustive-gc-app-flow
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -lexhaustive-gc-utils
        -lgcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        )