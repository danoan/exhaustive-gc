cmake_minimum_required(VERSION 3.8)
project(exhaustive_gc)

#CMAKE_INSTALL_PREFIX: install location

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic" )
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi" )

if(${USE_LOCAL_REPOSITORIES})
    include(ext-projects/ExtProjects.cmake)
endif()

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIB_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build/lib CACHE PATH "DIPaCUS libraries location path.")

set(GCURVE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "gcurve include location path.")
set(GCURVE_LIBS_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "gcurve librarie location path.")

set(GEOC_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "geoc include location path.")

set(LAZY-COMB_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "lazy-comb include location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_APPLICATIONS OFF CACHE BOOL "Build applications.")
set(CREATE_SHARED_LIBRARIES OFF CACHE BOOL "Build libraries as shared objects.")

link_directories(${CMAKE_BINARY_DIR}/modules/estimator
        ${CMAKE_BINARY_DIR}/modules/api
        ${CMAKE_BINARY_DIR}/modules/energy
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_SOURCE_DIR}/ext/lib
        ${DIPACUS_LIBS_DIR}
        ${GCURVE_LIBS_DIR}
        ${BOOST_LIBS_DIR})

add_subdirectory(modules/core)
add_subdirectory(modules/energy)
add_subdirectory(modules/api)
add_subdirectory(modules/utils)

if (${BUILD_TESTS})
    add_subdirectory(examples)
endif()

if (${BUILD_APPLICATIONS})
    add_subdirectory(app)
endif()

