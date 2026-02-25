cmake_minimum_required(VERSION 3.30)

project(mkbase
        VERSION 1.0
        LANGUAGES C CXX
        DESCRIPTION "Base library for all Monokuma project libs"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory("tests")
endif ()

include("${CMAKE_CURRENT_LIST_DIR}/CMake/mkbase.cmake")
