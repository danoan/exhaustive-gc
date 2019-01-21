cmake_minimum_required(VERSION 3.2)
project(exhaustive_gc_examples)

find_package(DGtal REQUIRED)

link_directories(${CMAKE_BINARY_DIR}/api
        ${CMAKE_BINARY_DIR}/dev
        ${DIPACUS_LIBS_DIR}
        ${BOOST_LIBS_DIR})

add_executable(examples-four-joint
        FourJointOptimalCurve.cpp)

target_compile_definitions(examples-four-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-four-joint PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/api/include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-four-joint PRIVATE
        -lgcurve
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES})



add_executable(examples-two-joint
        TwoJointOptimalCurve.cpp)

target_compile_definitions(examples-two-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-two-joint PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/api/include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-two-joint PRIVATE
        -lgcurve
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES})



add_executable(examples-one-exp-flow
        OneExpansionFlow.cpp)

target_compile_definitions(examples-one-exp-flow PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-one-exp-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/api/include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-one-exp-flow PRIVATE
        -lgcurve
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES})