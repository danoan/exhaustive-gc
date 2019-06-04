cmake_minimum_required(VERSION 3.8)
project(exhaustive_gc_base)

find_package(DGtal REQUIRED)

add_library(exhaustive-gc-base SHARED
        src/control/CurveFromJoints.cpp
        src/utils/SeparateInnerAndOuter.cpp)

set_target_properties(exhaustive-gc-base PROPERTIES
        COMPILE_FLAGS -fext-numeric-literals)

target_compile_features(exhaustive-gc-base PRIVATE cxx_auto_type)
target_include_directories(exhaustive-gc-base PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${LAZY-COMB_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        )

install(TARGETS exhaustive-gc-base
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})