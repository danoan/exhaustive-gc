cmake_minimum_required(VERSION 3.2)
project(exhaustive-gc-energy)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(exhaustive-gc-energy ${LIBRARY_ACTION}
        src/energy.cpp
        src/BaseMap.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(exhaustive-gc-energy geoc)
endif()

set_target_properties(exhaustive-gc-energy PROPERTIES
        VERSION ${VERSION_EXHAUSTIVE_GC_ENERGY})

target_include_directories(exhaustive-gc-energy PRIVATE
        include
        ${GEOC_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(exhaustive-gc-energy
        ${DGTAL_LIBRARIES})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS exhaustive-gc-energy
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)