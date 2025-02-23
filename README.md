# city

`city` is a JIT compiler infrastructure written in C++.

It provides a simple `llvm`-like builder API that is used to generate `city-ir`. This IR can then be compiled to any of
the supported architectures.

## Supported Platforms

`city` is tested and developed for support on the following platforms and compiler versions:

| OS            | Architecture | Compilers                   |
|---------------|--------------|-----------------------------|
| Windows 10/11 | Amd64/x86_64 | MSVC 2022, GCC 14, Clang 19 |
| MacOS 15      | AArch64      | Apple Clang 15              |
| MacOS 15      | Amd64/x86_64 | Apple Clang 15              |

Linux support is planned for GCC 14 and Clang 19.

## Goals

`city` aims to:

- Support `aarch64` and `amd64` on Windows, MacOS, and Linux.
- Be free of any third-party dependencies.
- Provide a simple API.
- Prioritize compilation speed over runtime speed in order to excel at compiling and running small, short-lived
  functions.