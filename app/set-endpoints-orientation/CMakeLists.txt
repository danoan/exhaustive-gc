cmake_minimum_required(VERSION 3.2)
project(set-endpoints-orientation)

find_package(OpenCV REQUIRED)

add_library(set-endpoints-orientation SHARED
        src/events.cpp
        src/utils.cpp
        src/gui.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(set-endpoints-orientation dipacus select-fixed-points)
else()
    add_dependencies(set-endpoints-orientation select-fixed-points)
endif()

set_target_properties(set-endpoints-orientation PROPERTIES COMPILE_FLAGS -fPIC)

target_link_directories(set-endpoints-orientation PRIVATE
        ${CMAKE_BINARY_DIR}/app/select-fixed-points)


target_include_directories(set-endpoints-orientation PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/app/select-fixed-points/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(set-endpoints-orientation
        -lselect-fixed-points
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

add_subdirectory(app)