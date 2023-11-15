cmake_minimum_required(VERSION 3.5.0)
project(CGrimoire VERSION 0.1.0 LANGUAGES C)

option(BUILD_TESTING "whether to build or not the tests" OFF)
option(BUILD_BENCHMARK "whether to build or not the benchmarks" OFF)

set(INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(vendor)

if(BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif(BUILD_TESTING)

if(BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif(BUILD_BENCHMARK)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)