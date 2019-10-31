cmake_minimum_required(VERSION 3.2)
project(app-summary-curve)

find_package(OpenCV REQUIRED)

add_executable(app-summary-curve summary-curve.cpp
        src/utils.cpp
        src/OneImageFlow.cpp
        src/InputReader.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(app-summary-curve dipacus)
endif()


target_link_directories(app-summary-curve PRIVATE
        ${CMAKE_BINARY_DIR}/app/select-fixed-points)

set_target_properties(app-summary-curve PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(app-summary-curve PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(app-summary-curve
        -lselect-fixed-points
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})