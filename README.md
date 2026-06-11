# wtl

[![build](https://github.com/tinysec/wtl/actions/workflows/ci.yaml/badge.svg)](https://github.com/tinysec/wtl/actions)
[![package](https://img.shields.io/badge/package-FetchContent-blue)](#use-from-another-cmake-project)

## Introduction

`wtl` packages Windows Template Library as a local CMake header-only dependency.
The CMake target is:

```cmake
wtl::wtl
```

Linking this target adds the WTL include directory to consumers, so existing WTL
includes continue to work:

```cpp
#include <atlapp.h>
#include <atlwin.h>
```

WTL requires a Windows C++ toolchain with ATL headers available.

## Use From Another CMake Project

Use `FetchContent` with a local checkout:

```cmake
include(FetchContent)

FetchContent_Declare(
        wtl
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../wtl")
FetchContent_MakeAvailable(wtl)

target_link_libraries(your_target PRIVATE wtl::wtl)
```

Known upstream package tags:

```text
v9.1.5321
v10.0.10320
v10.01
```

`master` tracks the latest packaged WTL version.
