cmake_minimum_required(VERSION 3.29)
project(city)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

add_library(city
        src/ir/value/Value.cpp
        src/ir/value/Value.h
        src/ir/type/Type.cpp
        src/ir/type/Type.h
        src/ir/Compiler.cpp
        src/ir/Compiler.h
        src/ir/Module.cpp
        src/ir/Module.h
        src/ir/Builder.cpp
        src/ir/Builder.h
        src/ir/instruction/Instruction.cpp
        src/ir/instruction/Instruction.h
        src/ir/Object.cpp
        src/ir/Object.h
        src/ir/Assembly.cpp
        src/ir/Assembly.h
        src/ir/value/ConstantValue.cpp
        src/ir/value/ConstantValue.h
        src/ir/value/PointerValue.cpp
        src/ir/value/PointerValue.h
        src/ir/Block.cpp
        src/ir/Block.h
        src/ir/Symbol.cpp
        src/ir/Symbol.h
        src/ir/Function.cpp
        src/ir/Function.h
        src/ir/instruction/arithmetic/AddInst.h
        src/ir/instruction/control/RetInst.h
        src/ir/instruction/control/BranchInst.h
        src/backend/Backend.cpp
        src/backend/Backend.h
        src/runtime/Runtime.h
        src/runtime/MacOS.cpp
        src/backend/aarch64/instruction/AArch64Instruction.cpp
        src/backend/aarch64/instruction/AArch64Instruction.h
        src/backend/aarch64/AArch64.cpp
        src/backend/aarch64/AArch64.h
        src/ir/Container.cpp
        src/ir/Container.h
        src/runtime/NativeMemoryHandle.cpp
        src/runtime/NativeMemoryHandle.h
        src/runtime/MacOS.h
        src/ir/instruction/memory/StoreInst.h
        src/ir/instruction/arithmetic/AddInst.cpp
        src/ir/instruction/control/RetInst.cpp
        src/ir/instruction/control/BranchInst.cpp
        src/ir/instruction/memory/StoreInst.cpp
        src/backend/x86/x86.cpp
        src/backend/x86/x86.h
        src/backend/IRTranslationInterface.h
        src/backend/x86/x86TranslationInterface.cpp
        src/backend/x86/x86TranslationInterface.h
        src/backend/x86/instruction/x86Instruction.cpp
        src/backend/x86/instruction/x86Instruction.h
        src/backend/x86/instruction/arithmetic/x86AddRM32Inst.h
        src/backend/x86/instruction/x86ModRM.cpp
        src/backend/x86/instruction/x86ModRM.h
        src/ByteBuffer.h
        src/backend/x86/instruction/arithmetic/x86AddMI32Inst.h
)
target_include_directories(city PUBLIC src)

add_executable(city-test
        test/city.test.cpp
)
target_link_libraries(city-test PRIVATE city GTest::gtest_main)