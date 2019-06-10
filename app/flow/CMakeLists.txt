cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-app-flow)

add_executable(exhaustive-gc-app-flow
        src/utils.cpp
        src/InputReader.cpp
        flow.cpp)

add_dependencies(exhaustive-gc-app-flow exhaustive-gc-api exhaustive-gc-energy exhaustive-gc-core exhaustive-gc-utils)

target_include_directories(exhaustive-gc-app-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/energy/include
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BTOOLS_INCLUDE_DIRS}
)

target_link_libraries(exhaustive-gc-app-flow
        -lexhaustive-gc-api
        -lexhaustive-gc-energy
        -lexhaustive-gc-core
        -lexhaustive-gc-utils
        -lgcurve
        -lgcurve-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        )