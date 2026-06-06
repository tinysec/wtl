cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED HELLO_VERSION OR HELLO_VERSION STREQUAL "")
    set(HELLO_VERSION "0.0.1")
endif()

project(hello VERSION "${HELLO_VERSION}" LANGUAGES C CXX)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(_hello_is_top_level TRUE)
else()
    set(_hello_is_top_level FALSE)
endif()

if(_hello_is_top_level)
    get_property(_is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(NOT _is_multi_config AND NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    endif()
endif()

include(GNUInstallDirs)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.cmake")

option(HELLO_BUILD_SHARED "Build hello as a shared library" OFF)
option(HELLO_INSTALL "Install the hello CMake package" "${_hello_is_top_level}")
option(BUILD_TEST "Build tests" OFF)

if(HELLO_BUILD_SHARED)
    add_library(hello SHARED
            src/hello.c)
else()
    add_library(hello STATIC
            src/hello.c)
endif()

add_library(hello::hello ALIAS hello)

target_include_directories(hello
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(HELLO_BUILD_SHARED)
    target_compile_definitions(hello
            PUBLIC
            HELLO_SHARED=1
            PRIVATE
            HELLO_BUILDING_LIBRARY=1
            BUILD_SHARED=1)
endif()

if(WIN32)
    target_compile_definitions(hello
            PRIVATE
            BUILD_R3
            WIN32_LEAN_AND_MEAN
            STRSAFE_NO_DEPRECATE
            _CRT_SECURE_NO_WARNINGS)
endif()

if(HELLO_BUILD_SHARED AND WIN32)
    enable_language(RC)

    set_target_properties(hello PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

    generate_version_header(
            VERSION "${PROJECT_VERSION}"
            PREFIX HELLO
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen/hello_version.h"
            REPO_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

    target_sources(hello
            PRIVATE
            src/main.c
            src/version.rc)

    target_include_directories(hello
            PRIVATE
            "${CMAKE_CURRENT_BINARY_DIR}/gen")

    if(MSVC)
        target_link_options(hello PRIVATE
                "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/src/export.def")
    else()
        target_sources(hello PRIVATE
                src/export.def)
    endif()

    target_link_libraries(hello PRIVATE kernel32)
endif()

if(HELLO_INSTALL)
    install(
            TARGETS hello
            EXPORT helloTargets
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")

    install(
            DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(
            EXPORT helloTargets
            FILE helloTargets.cmake
            NAMESPACE hello::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/hello")

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
            "${PROJECT_BINARY_DIR}/helloConfigVersion.cmake"
            VERSION "${PROJECT_VERSION}"
            COMPATIBILITY SameMajorVersion)

    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
            "${PROJECT_BINARY_DIR}/helloConfig.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/hello")

    install(
            FILES
            "${PROJECT_BINARY_DIR}/helloConfig.cmake"
            "${PROJECT_BINARY_DIR}/helloConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/hello")
endif()

if(BUILD_TEST)
    include(CTest)
    enable_testing()

    add_executable(hello_test
            test/hello_test.c)

    target_link_libraries(hello_test
            PRIVATE
            hello::hello)

    target_compile_definitions(hello_test
            PRIVATE
            BUILD_TEST=1)

    add_test(NAME hello_test COMMAND hello_test)
endif()
