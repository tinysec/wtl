# wtl

[![build](https://github.com/tinysec/wtl/actions/workflows/ci.yaml/badge.svg)](https://github.com/tinysec/wtl/actions)
[![package](https://img.shields.io/badge/package-FetchContent-blue)](#use-from-another-cmake-project)

## Introduction

`wtl` packages Windows Template Library as a CMake header-only dependency.
The exported CMake target is:

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

Use `FetchContent` and pin a specific tag:

```cmake
include(FetchContent)

FetchContent_Declare(
        wtl
        GIT_REPOSITORY https://github.com/tinysec/wtl.git
        GIT_TAG v10.01)
FetchContent_MakeAvailable(wtl)

target_link_libraries(your_target PRIVATE wtl::wtl)
```

Available tags:

```text
v9.1.5321
v10.0.10320
v10.01
```

`master` tracks the latest packaged WTL version.
