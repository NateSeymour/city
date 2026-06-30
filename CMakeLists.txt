cmake_minimum_required(VERSION 3.29)
project(city VERSION 0.4.4)

set(CMAKE_CXX_STANDARD 23)

add_custom_command(
        OUTPUT archc/IR.h
        COMMAND node ${CMAKE_SOURCE_DIR}/tools/archc/archc.js --input ${CMAKE_SOURCE_DIR}/arch/IR.arch --outputDir ${CMAKE_BINARY_DIR}/include/city
        DEPENDS ${CMAKE_SOURCE_DIR}/arch/IR.arch
)

add_custom_command(
        OUTPUT archc/AArch64.h
        COMMAND node ${CMAKE_SOURCE_DIR}/tools/archc/archc.js --input ${CMAKE_SOURCE_DIR}/arch/AArch64.arch --outputDir ${CMAKE_BINARY_DIR}/include/city
        DEPENDS ${CMAKE_SOURCE_DIR}/arch/AArch64.arch
)

add_custom_command(
        OUTPUT archc/Amd64.h
        COMMAND node ${CMAKE_SOURCE_DIR}/tools/archc/archc.js --input ${CMAKE_SOURCE_DIR}/arch/Amd64.arch --outputDir ${CMAKE_BINARY_DIR}/include/city
        DEPENDS ${CMAKE_SOURCE_DIR}/arch/Amd64.arch
)

add_library(city
        archc/IR.h
        archc/AArch64.h
        archc/Amd64.h

        include/city/ABI.h
        include/city/ABI.h
        include/city/arch/aarch64/AArch64.h
        include/city/arch/aarch64/AArch64Condition.h
        include/city/arch/aarch64/AArch64Function.h
        include/city/arch/aarch64/AArch64FunctionTranslator.h
        include/city/arch/aarch64/AArch64RegisterBank.h
        include/city/arch/aarch64/instruction/AArch64Instruction.h
        include/city/arch/aarch64/instruction/arithmetic/AArch64Add.h
        include/city/arch/aarch64/instruction/arithmetic/AArch64Cmp.h
        include/city/arch/aarch64/instruction/arithmetic/AArch64Div.h
        include/city/arch/aarch64/instruction/arithmetic/AArch64Mul.h
        include/city/arch/aarch64/instruction/arithmetic/AArch64Sub.h
        include/city/arch/aarch64/instruction/arithmetic/AArch64Sxt.h
        include/city/arch/aarch64/instruction/control/AArch64B.h
        include/city/arch/aarch64/instruction/control/AArch64Ret.h
        include/city/arch/aarch64/instruction/memory/AArch64Adr.h
        include/city/arch/aarch64/instruction/memory/AArch64Ldr.h
        include/city/arch/aarch64/instruction/memory/AArch64Mov.h
        include/city/arch/aarch64/instruction/memory/AArch64Str.h
        include/city/arch/amd64/Amd64Function.h
        include/city/arch/amd64/Amd64RegisterBank.h
        include/city/arch/amd64/instruction/arithmetic/Amd64Cqo.h
        include/city/arch/amd64/instruction/arithmetic/Amd64Div.h
        include/city/arch/amd64/instruction/arithmetic/Amd64Mul.h
        include/city/arch/amd64/instruction/arithmetic/Amd64Xor.h
        include/city/arch/amd64/instruction/control/Amd64Leave.h
        include/city/arch/amd64/instruction/memory/Amd64Lea.h
        include/city/arch/amd64/instruction/memory/Amd64Mov.h
        include/city/arch/amd64/instruction/memory/Amd64Pop.h
        include/city/arch/amd64/instruction/memory/Amd64Push.h
        include/city/arch/ir/block/IRBlock.h
        include/city/arch/ir/block/IRConditionalBlock.h
        include/city/arch/ir/IRBuilder.h
        include/city/arch/ir/IRCondition.h
        include/city/arch/ir/IRFunction.h
        include/city/arch/ir/IRModule.h
        include/city/Assembly.h
        include/city/ByteBuffer.h
        include/city/interface/InterfaceFunction.h
        include/city/interface/InterfaceModule.h
        include/city/Interop.h
        include/city/JIT.h
        include/city/module/Block.h
        include/city/module/container/ConstantDataContainer.h
        include/city/module/container/Container.h
        include/city/module/container/Register.h
        include/city/module/container/StackAllocationContainer.h
        include/city/module/container/StubContainer.h
        include/city/module/Function.h
        include/city/module/Module.h
        include/city/module/Module.h
        include/city/module/Type.h
        include/city/module/Value.h
        include/city/overload.h
        include/city/runtime/MacOS.h
        include/city/runtime/NativeMemoryHandle.h
        include/city/runtime/Runtime.h
        include/city/runtime/Windows.h
        include/city/Symbol.h
        include/city/transform/dbg/DebugPrinter.h
        include/city/transform/NativeModule.h
        lib/arch/aarch64/AArch64Condition.cpp
        lib/arch/aarch64/AArch64Function.cpp
        lib/arch/aarch64/AArch64FunctionTranslator.cpp
        lib/arch/aarch64/instruction/AArch64Instruction.cpp
        lib/arch/amd64/Amd64Function.cpp
        lib/arch/amd64/Amd64FunctionTranslator.cpp
        lib/arch/amd64/instruction/Amd64Instruction.cpp
        lib/arch/ir/block/IRBlock.cpp
        lib/arch/ir/block/IRConditionalBlock.cpp
        lib/arch/ir/IRBuilder.cpp
        lib/arch/ir/IRFunction.cpp
        lib/arch/ir/IRModule.cpp
        lib/Assembly.cpp
        lib/container/ConstantDataContainer.cpp
        lib/container/Container.cpp
        lib/container/Register.cpp
        lib/container/StackAllocationContainer.cpp
        lib/container/StubContainer.cpp
        lib/interface/InterfaceFunction.cpp
        lib/interface/InterfaceModule.cpp
        lib/JIT.cpp
        lib/runtime/MacOS.cpp
        lib/runtime/NativeMemoryHandle.cpp
        lib/runtime/Windows.cpp
        lib/Symbol.cpp
        lib/transform/Backend.cpp
        lib/transform/IRTranslator.cpp
        lib/transform/NativeInstruction.cpp
        lib/transform/NativeModule.cpp
        lib/value/ConstantValue.cpp
        lib/value/Value.cpp
)
target_include_directories(city PUBLIC include)
target_include_directories(city PUBLIC ${CMAKE_BINARY_DIR}/include)

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
            test/arch/ir.test.cpp
    )
    target_link_libraries(city-test PRIVATE city GTest::gtest_main)
endif ()