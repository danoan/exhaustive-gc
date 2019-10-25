cmake_minimum_required(VERSION 3.2)
project(app-select-fixed-points)

find_package(OpenCV REQUIRED)

add_executable(app-select-fixed-points select-fixed-points.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(app-select-fixed-points dipacus select-fixed-points)
else()
    add_dependencies(app-select-fixed-points dipacus select-fixed-points)
endif()


target_link_directories(app-select-fixed-points PRIVATE
        ${CMAKE_BINARY_DIR}/app/select-fixed-points)

set_target_properties(app-select-fixed-points PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(app-select-fixed-points PRIVATE
        ../include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(app-select-fixed-points
        -lselect-fixed-points
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})