cmake_minimum_required(VERSION 3.2)
project(lib_api_exhaustive_gc)

add_library(exhaustive-gc-api SHARED
        src/utils/GenerateSeedPairs.cpp
        src/utils/FilterSeedPairs.cpp
        src/utils/ImageFromCurve.cpp
        src/utils/InitImage.cpp
        include/exhaustive-gc/api/api.hpp)

add_dependencies(exhaustive-gc-api exhaustive-gc-base)

target_include_directories(exhaustive-gc-api PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${LAZY-COMB_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS})