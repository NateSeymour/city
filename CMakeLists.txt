cmake_minimum_required(VERSION 3.29)
project(city)

set(CMAKE_CXX_STANDARD 23)

add_library(city src/main.cpp
        src/ir/Value.cpp
        src/ir/Value.h
        src/ir/Type.cpp
        src/ir/Type.h
        src/ir/Compiler.cpp
        src/ir/Compiler.h
        src/ir/Module.cpp
        src/ir/Module.h
        src/ir/Builder.cpp
        src/ir/Builder.h
        src/ir/instruction/Instruction.cpp
        src/ir/instruction/Instruction.h)
