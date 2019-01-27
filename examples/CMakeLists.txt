cmake_minimum_required(VERSION 3.2)
project(exhaustive_gc_examples)


add_executable(examples-four-joint
        FourJointOptimalCurve.cpp)

target_compile_definitions(examples-four-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-four-joint PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/api/include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-four-joint PRIVATE
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -lgcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})



add_executable(examples-two-joint
        TwoJointOptimalCurve.cpp)

target_compile_definitions(examples-two-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-two-joint PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/api/include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS})

target_link_libraries(examples-two-joint PRIVATE
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -lgcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        )



add_executable(examples-one-exp-flow
        OneExpansionFlow.cpp)

target_compile_definitions(examples-one-exp-flow PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-one-exp-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/api/include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-one-exp-flow PRIVATE
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -lgcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

add_dependencies(examples-four-joint exhaustive-gc-api exhaustive-gc-base)
add_dependencies(examples-two-joint exhaustive-gc-api exhaustive-gc-base)
add_dependencies(examples-one-exp-flow exhaustive-gc-api exhaustive-gc-base)