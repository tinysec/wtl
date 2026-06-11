cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED WTL_VERSION OR WTL_VERSION STREQUAL "")
    set(WTL_VERSION "10.01")
endif()

project(wtl VERSION "${WTL_VERSION}" LANGUAGES CXX)

add_library(wtl INTERFACE)
add_library(wtl::wtl ALIAS wtl)

target_include_directories(wtl
        INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/wtl")
