cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-examples-one-expansion-flow)


add_executable(examples-one-exp-flow
        OneExpansionFlow.cpp)

target_compile_definitions(examples-one-exp-flow PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

add_dependencies(examples-one-exp-flow exhaustive-gc-api exhaustive-gc-energy exhaustive-gc-core exhaustive-gc-utils)

target_compile_definitions(examples-one-exp-flow PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(examples-one-exp-flow PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/energy/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${GEOC_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-one-exp-flow PRIVATE
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

install(TARGETS examples-one-exp-flow
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})