cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-utils)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(exhaustive-gc-utils ${LIBRARY_ACTION}
        src/timer.cpp
        src/digital.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(exhaustive-gc-utils dipacus gcurve)
endif()

target_include_directories(exhaustive-gc-utils PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(exhaustive-gc-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES})


install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS exhaustive-gc-utils
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)