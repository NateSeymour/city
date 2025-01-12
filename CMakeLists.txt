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
        src/Assembly.cpp
        src/Assembly.h
        src/ByteBuffer.h
        src/Container.cpp
        src/Container.h
        src/JIT.cpp
        src/JIT.h
        src/Object.cpp
        src/Object.h
        src/Symbol.cpp
        src/Symbol.h
        src/backend/Backend.cpp
        src/backend/Backend.h
        src/backend/IRTranslator.h
        src/backend/NativeInstruction.cpp
        src/backend/NativeInstruction.h
        src/backend/aarch64/AArch64.cpp
        src/backend/aarch64/AArch64.h
        src/backend/aarch64/instruction/AArch64Instruction.cpp
        src/backend/aarch64/instruction/AArch64Instruction.h
        src/backend/amd64/Amd64.cpp
        src/backend/amd64/Amd64.h
        src/backend/amd64/Amd64Builder.cpp
        src/backend/amd64/Amd64Builder.h
        src/backend/amd64/Amd64ModRM.h
        src/backend/amd64/Amd64Module.cpp
        src/backend/amd64/Amd64Module.h
        src/backend/amd64/Amd64Register.cpp
        src/backend/amd64/Amd64Register.h
        src/backend/amd64/Amd64Translator.cpp
        src/backend/amd64/Amd64Translator.h
        src/backend/amd64/instruction/Amd64Instruction.cpp
        src/backend/amd64/instruction/Amd64Instruction.h
        src/backend/amd64/instruction/control/Amd64Ret.h
        src/backend/amd64/instruction/memory/Amd64Mov.h
        src/backend/amd64/instruction/memory/Amd64Pop.h
        src/backend/amd64/instruction/memory/Amd64Push.h
        src/ir/IRBuilder.cpp
        src/ir/IRBuilder.h
        src/ir/IRFunction.cpp
        src/ir/IRFunction.h
        src/ir/IRModule.cpp
        src/ir/IRModule.h
        src/ir/block/IRBlock.cpp
        src/ir/block/IRBlock.h
        src/ir/instruction/IRInstruction.cpp
        src/ir/instruction/IRInstruction.h
        src/ir/instruction/InstructionFunctor.h
        src/ir/instruction/arithmetic/AddInst.cpp
        src/ir/instruction/arithmetic/AddInst.h
        src/ir/instruction/control/BranchInst.cpp
        src/ir/instruction/control/BranchInst.h
        src/ir/instruction/control/RetInst.cpp
        src/ir/instruction/control/RetInst.h
        src/ir/instruction/memory/StoreInst.cpp
        src/ir/instruction/memory/StoreInst.h
        src/runtime/MacOS.cpp
        src/runtime/MacOS.h
        src/runtime/NativeMemoryHandle.cpp
        src/runtime/NativeMemoryHandle.h
        src/runtime/Runtime.h
        src/runtime/Windows.cpp
        src/runtime/Windows.h
        src/type/Type.cpp
        src/type/Type.h
        src/value/ConstantValue.cpp
        src/value/ConstantValue.h
        src/value/Value.cpp
        src/value/Value.h
        src/ir/instruction/IRBinaryInstruction.cpp
        src/ir/instruction/IRBinaryInstruction.h
        src/backend/amd64/instruction/arithmetic/Amd64Add.h
)
target_include_directories(city PUBLIC src)

add_executable(city-test
        test/module.test.cpp
        test/amd64.test.cpp
)
target_link_libraries(city-test PRIVATE city GTest::gtest_main)