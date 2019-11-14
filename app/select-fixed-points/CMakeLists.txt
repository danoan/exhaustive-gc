cmake_minimum_required(VERSION 3.2)
project(select-fixed-points)

find_package(OpenCV REQUIRED)

add_library(select-fixed-points SHARED
        src/gui.cpp
        src/utils.cpp
        src/events.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(select-fixed-points dipacus)
endif()


set_target_properties(select-fixed-points PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(select-fixed-points PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(select-fixed-points
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS select-fixed-points
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)