cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED WTL_VERSION OR WTL_VERSION STREQUAL "")
    set(WTL_VERSION "10.01")
endif()

project(wtl VERSION "${WTL_VERSION}" LANGUAGES CXX)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(_wtl_is_top_level TRUE)
else()
    set(_wtl_is_top_level FALSE)
endif()

include(GNUInstallDirs)

option(WTL_INSTALL "Install the wtl CMake package" "${_wtl_is_top_level}")

add_library(wtl INTERFACE)
add_library(wtl::wtl ALIAS wtl)

target_include_directories(wtl
        INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/wtl>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/wtl>")

if(WTL_INSTALL)
    install(
            TARGETS wtl
            EXPORT wtlTargets)

    install(
            DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/wtl/"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/wtl")

    install(
            FILES "${CMAKE_CURRENT_SOURCE_DIR}/license.txt"
            DESTINATION "${CMAKE_INSTALL_DOCDIR}")

    install(
            EXPORT wtlTargets
            FILE wtlTargets.cmake
            NAMESPACE wtl::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/wtl")

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
            "${PROJECT_BINARY_DIR}/wtlConfigVersion.cmake"
            VERSION "${PROJECT_VERSION}"
            COMPATIBILITY SameMajorVersion)

    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
            "${PROJECT_BINARY_DIR}/wtlConfig.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/wtl")

    install(
            FILES
            "${PROJECT_BINARY_DIR}/wtlConfig.cmake"
            "${PROJECT_BINARY_DIR}/wtlConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/wtl")
endif()
