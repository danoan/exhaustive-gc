cmake_minimum_required(VERSION 3.8)
project(exhaustive_gc_core)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED" include/exhaustive-gc/core/checker/IMarkedMapChecker.h include/exhaustive-gc/core/check-elem/CCheckableElement.h)
endif()

add_library(exhaustive-gc-core ${LIBRARY_ACTION}
        src/control/CurveFromJoints.cpp
        src/control/FindCandidate.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(exhaustive-gc-core dipacus gcurve magLac exhaustive-gc-energy)
else()
    add_dependencies(exhaustive-gc-core exhaustive-gc-energy)
endif()

set_target_properties(exhaustive-gc-core PROPERTIES
        COMPILE_FLAGS -fext-numeric-literals
        VERSION ${VERSION_EXHAUSTIVE_GC_CORE})

target_compile_features(exhaustive-gc-core PRIVATE cxx_auto_type)
target_include_directories(exhaustive-gc-core PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/energy/include
        ${DIPACUS_INCLUDE_DIRS}
        ${GCURVE_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        )

install(TARGETS exhaustive-gc-core
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})