cmake_minimum_required(VERSION 3.8)
project(exhaustive_gc)


add_subdirectory(dev)
add_subdirectory(api)

find_package(DGtal REQUIRED)

link_directories(ext/lib cmake-build-debug/api cmake-build-debug/dev ${CMAKE_PREFIX_PATH})

add_executable(main main.cpp)
add_dependencies(main exhaustive-gc-api exhaustive-gc-base)

target_include_directories(main PRIVATE
        dev/include
        api/include
        ext/include
        ${DGTAL_INCLUDE_DIRS}
        )

target_link_libraries(main
        -lgcurve
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lexhaustive-gc-api
        -lexhaustive-gc-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES})