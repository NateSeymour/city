cmake_minimum_required(VERSION 3.29)
project(city VERSION 0.3.11)

set(CMAKE_CXX_STANDARD 23)

add_library(city
        include/city/ABI.h
        include/city/Assembly.h
        include/city/backend/aarch64/AArch64.h
        include/city/backend/aarch64/instruction/AArch64Instruction.h
        include/city/backend/amd64/Amd64Function.h
        include/city/backend/amd64/Amd64RegisterBank.h
        include/city/backend/amd64/instruction/arithmetic/Amd64Div.h
        include/city/backend/amd64/instruction/arithmetic/Amd64Mul.h
        include/city/backend/amd64/instruction/control/Amd64Leave.h
        include/city/ByteBuffer.h
        include/city/container/ConstantDataContainer.h
        include/city/container/Container.h
        include/city/container/StackAllocationContainer.h
        include/city/Function.h
        include/city/interface/InterfaceFunction.h
        include/city/interface/InterfaceModule.h
        include/city/ir/block/IRBlock.h
        include/city/ir/instruction/arithmetic/AddInst.h
        include/city/ir/instruction/arithmetic/DivInst.h
        include/city/ir/instruction/arithmetic/MulInst.h
        include/city/ir/instruction/arithmetic/SubInst.h
        include/city/ir/instruction/control/CallInst.h
        include/city/ir/instruction/control/RetInst.h
        include/city/ir/instruction/IRBinaryInstruction.h
        include/city/ir/instruction/IRInstruction.h
        include/city/ir/IRBuilder.h
        include/city/ir/IRFunction.h
        include/city/ir/IRModule.h
        include/city/JIT.h
        include/city/overload.h
        include/city/runtime/MacOS.h
        include/city/runtime/NativeMemoryHandle.h
        include/city/runtime/Runtime.h
        include/city/runtime/Windows.h
        include/city/Symbol.h
        include/city/type/Type.h
        include/city/value/Value.h
        lib/Assembly.cpp
        lib/backend/aarch64/AArch64.cpp
        lib/backend/aarch64/instruction/AArch64Instruction.cpp
        lib/backend/amd64/Amd64.cpp
        lib/backend/amd64/Amd64Function.cpp
        lib/backend/amd64/Amd64FunctionTranslator.cpp
        lib/container/Register.cpp
        lib/backend/amd64/instruction/Amd64Instruction.cpp
        lib/backend/Backend.cpp
        lib/backend/NativeInstruction.cpp
        lib/container/ConstantDataContainer.cpp
        lib/container/Container.cpp
        lib/container/StackAllocationContainer.cpp
        lib/Function.cpp
        lib/interface/InterfaceFunction.cpp
        lib/interface/InterfaceModule.cpp
        lib/ir/block/IRBlock.cpp
        lib/ir/instruction/arithmetic/AddInst.cpp
        lib/ir/instruction/arithmetic/DivInst.cpp
        lib/ir/instruction/arithmetic/MulInst.cpp
        lib/ir/instruction/arithmetic/SubInst.cpp
        lib/ir/instruction/control/CallInst.cpp
        lib/ir/instruction/control/RetInst.cpp
        lib/ir/instruction/IRBinaryInstruction.cpp
        lib/ir/instruction/IRInstruction.cpp
        lib/ir/IRBuilder.cpp
        lib/ir/IRFunction.cpp
        lib/ir/IRModule.cpp
        lib/JIT.cpp
        lib/runtime/MacOS.cpp
        lib/runtime/NativeMemoryHandle.cpp
        lib/runtime/Windows.cpp
        lib/Symbol.cpp
        lib/value/Value.cpp
        include/city/backend/NativeModule.h
        include/city/backend/aarch64/AArch64Function.h
        include/city/backend/aarch64/AArch64FunctionTranslator.h
        include/city/container/Register.h
        include/city/backend/aarch64/AArch64RegisterBank.h
        lib/backend/aarch64/AArch64FunctionTranslator.cpp
        lib/backend/aarch64/AArch64Function.cpp
        lib/backend/NativeModule.cpp
        include/city/backend/aarch64/instruction/arithmetic/AArch64Add.h
        lib/backend/IRTranslator.cpp
        include/city/backend/aarch64/instruction/control/AArch64Ret.h
        include/city/value/ConstantValue.h
        lib/value/ConstantValue.cpp
        include/city/backend/aarch64/instruction/memory/AArch64Mov.h
        include/city/backend/aarch64/instruction/arithmetic/AArch64Div.h
        include/city/backend/aarch64/instruction/arithmetic/AArch64Mul.h
        include/city/container/StubContainer.h
        lib/container/StubContainer.cpp
)
target_include_directories(city PUBLIC include)

#if (MSVC)
#    target_compile_options(city PRIVATE /W4 /WX)
#else ()
#    target_compile_options(city PRIVATE -Wall -Wextra -Wpedantic -Werror)
#endif ()

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
            test/jit.test.cpp
    )
    target_link_libraries(city-test PRIVATE city GTest::gtest_main)
endif ()