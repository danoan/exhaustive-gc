cmake_minimum_required(VERSION 3.2)
project(lib_api_exhaustive_gc)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(exhaustive-gc-api ${LIBRARY_ACTION}
        src/utils/GenerateSeedPairs.cpp
        src/utils/FilterSeedPairs.cpp
        src/utils/InitImage.cpp
        include/exhaustive-gc/api/api.hpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(exhaustive-gc-api dipacus gcurve lazy-combinator exhaustive-gc-core)
else()
    add_dependencies(exhaustive-gc-api exhaustive-gc-core)
endif()


target_include_directories(exhaustive-gc-api PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${LAZY-COMB_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS exhaustive-gc-api
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)