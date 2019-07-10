cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-examples-two-joints)

add_executable(examples-two-joint
        TwoJointOptimalCurve.cpp)

target_compile_definitions(examples-two-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

add_dependencies(examples-two-joint exhaustive-gc-api exhaustive-gc-energy exhaustive-gc-core exhaustive-gc-utils)

target_compile_definitions(examples-two-joint PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-two-joint PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/energy/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS})

target_link_libraries(examples-two-joint PRIVATE
        -lexhaustive-gc-api
        -lexhaustive-gc-energy
        -lexhaustive-gc-core
        -lexhaustive-gc-utils
        -lgcurve
        -lgcurve-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        )

install(TARGETS examples-two-joint
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})