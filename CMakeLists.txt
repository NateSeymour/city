cmake_minimum_required(VERSION 3.29)
project(city VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 23)

add_library(city
        include/city/Assembly.h
        include/city/ByteBuffer.h
        include/city/container/ConstantDataContainer.h
        include/city/container/Container.h
        include/city/ir/block/IRBlock.h
        include/city/ir/instruction/arithmetic/AddInst.h
        include/city/ir/instruction/arithmetic/SubInst.h
        include/city/ir/instruction/control/CallInst.h
        include/city/ir/instruction/control/RetInst.h
        include/city/ir/instruction/IRBinaryInstruction.h
        include/city/ir/instruction/IRInstruction.h
        include/city/ir/IRBuilder.h
        include/city/ir/IRFunction.h
        include/city/ir/IRModule.h
        include/city/JIT.h
        include/city/Object.h
        include/city/runtime/MacOS.h
        include/city/runtime/NativeMemoryHandle.h
        include/city/runtime/Runtime.h
        include/city/runtime/Windows.h
        include/city/Symbol.h
        include/city/type/Type.h
        include/city/Value.h
        lib/Assembly.cpp
        lib/backend/aarch64/AArch64.cpp
        lib/backend/aarch64/AArch64.h
        lib/backend/aarch64/instruction/AArch64Instruction.cpp
        lib/backend/aarch64/instruction/AArch64Instruction.h
        lib/backend/amd64/Amd64.cpp
        lib/backend/amd64/Amd64FunctionTranslator.cpp
        lib/backend/amd64/container/Amd64Register.cpp
        lib/backend/amd64/container/Amd64RegisterLoader.cpp
        lib/backend/amd64/instruction/Amd64Instruction.cpp
        lib/backend/Backend.cpp
        lib/backend/NativeInstruction.cpp
        lib/container/ConstantDataContainer.cpp
        lib/container/Container.cpp
        lib/ir/block/IRBlock.cpp
        lib/ir/instruction/arithmetic/AddInst.cpp
        lib/ir/instruction/arithmetic/SubInst.cpp
        lib/ir/instruction/control/CallInst.cpp
        lib/ir/instruction/control/RetInst.cpp
        lib/ir/instruction/IRBinaryInstruction.cpp
        lib/ir/instruction/IRInstruction.cpp
        lib/ir/IRBuilder.cpp
        lib/ir/IRFunction.cpp
        lib/ir/IRModule.cpp
        lib/JIT.cpp
        lib/Object.cpp
        lib/runtime/MacOS.cpp
        lib/runtime/NativeMemoryHandle.cpp
        lib/runtime/Windows.cpp
        lib/Value.cpp
        lib/Symbol.cpp
        include/city/type/PointerType.h
        include/city/type/FunctionType.h
        include/city/type/ScalarType.h
        include/city/type/FloatingPointType.h
        include/city/backend/amd64/Amd64Module.h
        lib/backend/amd64/Amd64Module.cpp
        include/city/backend/amd64/container/Amd64RegisterBank.h
        include/city/backend/amd64/instruction/control/Amd64Leave.h
        include/city/backend/amd64/Amd64Function.h
        lib/backend/amd64/Amd64Function.cpp
        include/city/container/StackAllocationContainer.h
        lib/container/StackAllocationContainer.cpp
)
target_include_directories(city PUBLIC include)

option(CITY_ENABLE_TESTS "Include googletest and enable test targets" ON)
if (CITY_ENABLE_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG main
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(city-test
            test/module.test.cpp
            test/amd64.test.cpp
    )
    target_link_libraries(city-test PRIVATE city GTest::gtest_main)
endif ()