cmake_minimum_required(VERSION 3.2)
project(app-exhaustive-gc-flow)

add_executable(app-exhaustive-gc-flow
        src/utils.cpp
        src/InputReader.cpp
        flow.cpp)

add_dependencies(app-exhaustive-gc-flow exhaustive-gc-api exhaustive-gc-energy exhaustive-gc-core exhaustive-gc-utils select-fixed-points set-endpoints-orientation)

target_link_directories(app-exhaustive-gc-flow PRIVATE
        ${CMAKE_BINARY_DIR}/app/select-fixed-points
        ${CMAKE_BINARY_DIR}/app/set-endpoints-orientation)

target_include_directories(app-exhaustive-gc-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/energy/include
        ${CMAKE_SOURCE_DIR}/modules/api/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/app/select-fixed-points/include
        ${CMAKE_SOURCE_DIR}/app/set-endpoints-orientation/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BTOOLS_INCLUDE_DIRS}
)

target_link_libraries(app-exhaustive-gc-flow
        -lset-endpoints-orientation
        -lselect-fixed-points
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
        ${OpenCV_LIBS}
        )

install(TARGETS app-exhaustive-gc-flow
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})