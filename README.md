# wtl

[![build](https://github.com/tinysec/wtl/actions/workflows/ci.yaml/badge.svg)](https://github.com/tinysec/wtl/actions)
[![usage](https://img.shields.io/badge/usage-FetchContent-blue)](#use-from-another-cmake-project)

## Introduction

`wtl` exposes Windows Template Library as a CMake header-only dependency.
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

Use `FetchContent` to load this repository from GitHub:

```cmake
include(FetchContent)

FetchContent_Declare(
        wtl
        GIT_REPOSITORY https://github.com/tinysec/wtl.git
        GIT_TAG v10.01)
FetchContent_MakeAvailable(wtl)

target_link_libraries(your_target PRIVATE wtl::wtl)
```

This repository is intended to be consumed with `FetchContent`; it does not
provide CMake install or package configuration support.
