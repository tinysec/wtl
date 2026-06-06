# wtl

[![build](https://github.com/tinysec/wtl/actions/workflows/ci.yaml/badge.svg)](https://github.com/tinysec/wtl/actions)
[![package](https://img.shields.io/badge/package-FetchContent%20%7C%20find_package-blue)](#use-from-another-cmake-project)

## Introduction

`wtl` packages Windows Template Library 10.10.10320 as a CMake header-only
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
find_package(wtl 10.10.10320 EXACT CONFIG REQUIRED)
```

Point `CMAKE_PREFIX_PATH` at the installation prefix if CMake cannot find it:

```cmd
cmake -S . -B build -DCMAKE_PREFIX_PATH=C:\path\to\install\wtl
```

## Component Libraries

Header-only component libraries that use WTL should depend on `wtl::wtl` instead
of vendoring their own copy:

```cmake
find_package(wtl 10.10.10320 CONFIG REQUIRED)

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

## Version Branches

This repository uses one branch per WTL version line, without a `release/`
prefix:

```text
9.1    -> WTL source from D:\code\wtl-origin\9.1.5321, tag v9.1.5321
10.01  -> WTL source from D:\code\wtl-origin\10.01, tag v10.01
10.10  -> WTL source from D:\code\wtl-origin\10.10.10320, tag v10.10.10320
```

Each branch keeps the same package layout. Only `Include` from the upstream WTL
source is copied into `include/wtl`; samples and AppWizard files are not part of
this CMake package.

Import a version into the current branch:

```powershell
.\tools\import-wtl-version.ps1 -Version 10.10.10320 -SourceRoot D:\code\wtl-origin
```

Then verify, commit, push the branch, and tag the exact release:

```cmd
cmake -S . -B build -DWTL_INSTALL=ON
cmake --install build --prefix install\wtl
git tag v10.10.10320
git push github 10.10 v10.10.10320
```
