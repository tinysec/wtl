# wtl

[![build](https://github.com/tinysec/wtl/actions/workflows/ci.yaml/badge.svg)](https://github.com/tinysec/wtl/actions)
[![package](https://img.shields.io/badge/package-FetchContent%20%7C%20find_package-blue)](#use-from-another-cmake-project)

## Introduction

`wtl` packages Windows Template Library 10.0.10320 as a CMake header-only
dependency.
It does not build a library artifact. The exported CMake target is:

```cmake
wtl::wtl
```

Linking this target adds the WTL include directory to consumers, so existing WTL
includes continue to work:

```cpp
#include <atlapp.h>
#include <atlwin.h>
```

WTL still requires a Windows C++ toolchain with ATL headers available.

## Use From Another CMake Project

### FetchContent

```cmake
include(FetchContent)

FetchContent_Declare(
        wtl
        GIT_REPOSITORY https://github.com/tinysec/wtl.git
        GIT_TAG master)
FetchContent_MakeAvailable(wtl)

target_link_libraries(your_target PRIVATE wtl::wtl)
```

### Installed Package

Build and install the package:

```cmd
cmake -S . -B build -DWTL_INSTALL=ON
cmake --install build --prefix install\wtl
```

Consumers then use the installed package:

```cmake
find_package(wtl CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE wtl::wtl)
```

Consumers that need this exact WTL package version can request it explicitly:

```cmake
find_package(wtl 10.0.10320 EXACT CONFIG REQUIRED)
```

Point `CMAKE_PREFIX_PATH` at the installation prefix if CMake cannot find it:

```cmd
cmake -S . -B build -DCMAKE_PREFIX_PATH=C:\path\to\install\wtl
```

## Component Libraries

Header-only component libraries that use WTL should depend on `wtl::wtl` instead
of vendoring their own copy:

```cmake
find_package(wtl 10.0.10320 CONFIG REQUIRED)

add_library(component_a INTERFACE)
add_library(component_a::component_a ALIAS component_a)

target_include_directories(component_a INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>")

target_link_libraries(component_a INTERFACE wtl::wtl)
```

If the component library is installed as a CMake package, its
`Config.cmake.in` should forward the dependency:

```cmake
@PACKAGE_INIT@

include(CMakeFindDependencyMacro)
find_dependency(wtl CONFIG REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/component_aTargets.cmake")

check_required_components("@PROJECT_NAME@")
```

Applications can then link only the component targets; WTL is pulled in through
their public interface.

## Build

Because this package is header-only, local build verification is just configure
and install:

```cmd
cmake -S . -B build
cmake --install build --prefix install\wtl
```
