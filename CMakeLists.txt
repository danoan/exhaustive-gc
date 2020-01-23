cmake_minimum_required(VERSION 3.8)


set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(EXTPROJECTS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext-projects/source)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/cmake-build-release)
else()
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/cmake-build-debug)
endif ()

set(CMAKE_CXX_STANDARD 14)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")


set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIB_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "DIPaCUS libraries location path.")

set(GCURVE_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "gcurve include location path.")
set(GCURVE_LIBS_DIR ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "gcurve librarie location path.")

set(GEOC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "geoc include location path.")
set(MAGLAC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "magLac include location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_APPLICATIONS ON CACHE BOOL "Build applications.")
set(CREATE_SHARED_LIBRARIES ON CACHE BOOL "Build libraries as shared objects.")

project(exhaustive_gc)

if(${USE_REMOTE_REPOSITORIES})
    include(ext-projects/ExtProjects.cmake)
endif()

set(VERSION_EXHAUSTIVE_GC_API v0.2)
set(VERSION_EXHAUSTIVE_GC_CORE v0.2)
set(VERSION_EXHAUSTIVE_GC_ENERGY v0.2)
set(VERSION_EXHAUSTIVE_GC_UTILS v0.2)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

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

endif()

if (${BUILD_EXAMPLES})
    add_subdirectory(lab/examples)
endif()

if (${BUILD_APPLICATIONS})
    add_subdirectory(app)
endif()

