cmake_minimum_required(VERSION 3.2)
project(app-set-endpoints-orientation)

find_package(OpenCV REQUIRED)

add_executable(app-set-endpoints-orientation app-set-endpoints-orientation.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(app-set-endpoints-orientation dipacus select-fixed-points set-endpoints-orientation)
else()
    add_dependencies(app-set-endpoints-orientation select-fixed-points set-endpoints-orientation)
endif()

set_target_properties(app-set-endpoints-orientation PROPERTIES COMPILE_FLAGS -fPIC)

target_link_directories(app-set-endpoints-orientation PRIVATE
        ${CMAKE_BINARY_DIR}/app/select-fixed-points
        ${CMAKE_BINARY_DIR}/app/set-endpoints-orientation)


target_include_directories(app-set-endpoints-orientation PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/app/select-fixed-points/include
        ${CMAKE_SOURCE_DIR}/app/set-endpoints-orientation/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(app-set-endpoints-orientation
        -lset-endpoints-orientation
        -lselect-fixed-points
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})