# city

`city` is a JIT compiler infrastructure written in C++.

It provides a simple `llvm`-like builder API that is used to generate `city` IR. This IR can then be compiled (or
cross-compiled) to any of the supported architectures.

## Goals

`city` aims to:

- Support `aarch64` and `amd64` on Windows, MacOS, and Linux.
- Be free of any third-party dependencies.
- Provide a simple API.
- Prioritize compilation speed over runtime speed in order to excel at compiling and running small, short-lived
  functions.
- Support, but not prioritize, static compilation to native object files that can be linked against.