cmake_minimum_required(VERSION 3.8)
project(exhaustive_gc)

find_package(DGtal REQUIRED)

add_library(exhaustive-gc INTERFACE)
target_compile_features(exhaustive-gc INTERFACE cxx_auto_type)
target_include_directories(exhaustive-gc INTERFACE
        include
        ext/include)

add_executable(main main.cpp)
target_include_directories(main PRIVATE
        include
        ext/include)