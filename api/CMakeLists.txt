cmake_minimum_required(VERSION 3.2)
project(lib_api_exhaustive_gc)

find_package(DGtal REQUIRED)

add_library(exhaustive-gc-api SHARED
        src/utils/GenerateSeedPairs.cpp
        src/utils/FilterSeedPairs.cpp
        src/utils/ImageFromCurve.cpp
        src/utils/InitImage.cpp
        src/api.cpp)

add_dependencies(exhaustive-gc-api exhaustive-gc-base)

target_include_directories(exhaustive-gc-api PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${DGTAL_INCLUDE_DIRS})