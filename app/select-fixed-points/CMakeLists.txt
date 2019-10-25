cmake_minimum_required(VERSION 3.2)
project(app-select-fixed-points)

find_package(OpenCV REQUIRED)

add_executable(app-select-fixed-points select-fixed-points.cpp)

set_target_properties(app-select-fixed-points PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(app-select-fixed-points PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(app-select-fixed-points
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})