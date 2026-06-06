# hello

[![build](https://git.tinysec.net/tcode/cmake-library/actions/workflows/ci.yaml/badge.svg)](https://git.tinysec.net/tcode/cmake-library/actions)
[![arch](https://img.shields.io/badge/arch-i386%20%7C%20amd64-blue)](#wdk7-build)
[![build](https://img.shields.io/badge/build-CMake%20%7C%20WDK7-blue)](#build)
[![package](https://img.shields.io/badge/package-FetchContent%20%7C%20find_package-blue)](#use-from-another-cmake-project)

## Introduction

`hello` is a minimal C library template for CMake projects. It is designed to
work both as a source dependency through `FetchContent` and as an installed
CMake config package through `find_package(hello CONFIG REQUIRED)`.

The CMake target is named `hello`. On Unix-like platforms the library artifact
uses the normal platform prefix, such as `libhello.a` or `libhello.so`. On
Windows and WDK7 builds the artifacts are `hello.lib` and, for shared builds,
`hello.dll`.

The library builds as a static library by default. Public CMake options and
exported compile definitions use the `HELLO_` prefix. Callers can explicitly
switch to a DLL by setting `HELLO_BUILD_SHARED=ON`.

## Use From Another CMake Project

### FetchContent

Static library, the default:

```cmake
include(FetchContent)

FetchContent_Declare(
        hello
        GIT_REPOSITORY git@git.tinysec.net:tcode/cmake-library.git
        GIT_TAG master)
FetchContent_MakeAvailable(hello)

target_link_libraries(your_target PRIVATE hello::hello)
```

DLL build:

```cmake
include(FetchContent)

set(HELLO_BUILD_SHARED ON CACHE BOOL "Build hello as a DLL")

FetchContent_Declare(
        hello
        GIT_REPOSITORY git@git.tinysec.net:tcode/cmake-library.git
        GIT_TAG master)
FetchContent_MakeAvailable(hello)

target_link_libraries(your_target PRIVATE hello::hello)
```

### Installed Package

Build and install a static package:

```cmd
cmake -S . -B build-static -DHELLO_BUILD_SHARED=OFF -DHELLO_INSTALL=ON
cmake --build build-static --config Release
cmake --install build-static --config Release --prefix install\hello-static
```

Build and install a DLL package:

```cmd
cmake -S . -B build-shared -DHELLO_BUILD_SHARED=ON -DHELLO_INSTALL=ON
cmake --build build-shared --config Release
cmake --install build-shared --config Release --prefix install\hello-shared
```

Consumers then use the installed package:

```cmake
find_package(hello CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE hello::hello)
```

The static or DLL choice is made when `hello` is built and installed. The
consumer should point `CMAKE_PREFIX_PATH` at the matching installation prefix.

## Build

Default local build, static library:

```cmd
cmake -S . -B build
cmake --build build --config Release
```

Build a DLL:

```cmd
cmake -S . -B build-shared -DHELLO_BUILD_SHARED=ON
cmake --build build-shared --config Release
```

## Tests

Tests are disabled by default. Enable them with `BUILD_TEST=ON`.

```cmd
cmake -S . -B build-test -DBUILD_TEST=ON
cmake --build build-test --config Release
ctest --test-dir build-test -C Release --output-on-failure
```

## WDK7 Build

WDK7 builds use the repository toolchain file. `WDK7_ARCH` accepts `i386` or
`amd64`.

```cmd
cmake -S . -B build\wdk7-amd64 -G "NMake Makefiles" ^
      "-DCMAKE_TOOLCHAIN_FILE=cmake/wdk7.cmake" ^
      -DWDK7_ARCH=amd64 ^
      -DHELLO_BUILD_SHARED=ON ^
      -DBUILD_TEST=ON ^
      -DCMAKE_BUILD_TYPE=Release
cmake --build build\wdk7-amd64
ctest --test-dir build\wdk7-amd64 --output-on-failure
```

Use `-DHELLO_BUILD_SHARED=OFF` for a static library.
