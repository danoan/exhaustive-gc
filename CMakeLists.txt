cmake_minimum_required(VERSION 3.8)
project(exhaustive_gc)

#CMAKE_INSTALL_PREFIX: install location

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIB_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "DIPaCUS libraries location path.")

set(GCURVE_INCLUDE_DIRS /usr/local/include/gcurve CACHE PATH "gcurve include location path.")
set(GCURVE_LIBS_DIR /usr/local/lib CACHE PATH "gcurve librarie location path.")

set(LAZY-COMB_INCLUDE_DIRS /usr/local/include/gcurve CACHE PATH "lazy-comb include location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")

link_directories(${CMAKE_BINARY_DIR}/modules/estimator
        ${CMAKE_BINARY_DIR}/modules/api
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_SOURCE_DIR}/ext/lib
        ${DIPACUS_LIBS_DIR}
        ${GCURVE_LIBS_DIR}
        ${BOOST_LIBS_DIR})

add_subdirectory(modules/core)
add_subdirectory(modules/api)
add_subdirectory(modules/utils)

if (${BUILD_TESTS})
    add_subdirectory(examples)
endif()

