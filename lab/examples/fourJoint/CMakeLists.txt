cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-examples-four-joint)

add_executable(examples-four-joint
        FourJointOptimalCurve.cpp)

target_compile_definitions(examples-four-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

add_dependencies(examples-four-joint exhaustive-gc-api exhaustive-gc-energy exhaustive-gc-core exhaustive-gc-utils)

target_include_directories(examples-four-joint PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/energy/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-four-joint PRIVATE
        -lexhaustive-gc-utils
        -lexhaustive-gc-energy
        -lexhaustive-gc-api
        -lexhaustive-gc-core
        -lgcurve
        -lgcurve-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS examples-four-joint
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})