#include <JIT.h>
#include <gtest/gtest.h>
#include <ir/IRModule.h>

class Amd64TestRunner : public testing::Test
{
protected:
    city::JIT jit;

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(Amd64TestRunner, ReturnVoidFunction)
{
    city::IRModule module{"test_return_void"};
    auto builder = module.CreateBuilder();

    auto function = builder.CreateFunction("test_return_void");
    builder.SetInsertPoint(function);

    builder.InsertRetInst(nullptr);

    this->jit.AddIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test_symbol = assembly.Lookup("test_return_void");
    auto test = test_symbol.ToPointer<void()>();

    test();

    this->jit.RemoveModule("test_return_void");
}

TEST_F(Amd64TestRunner, ReturnConstantFunction)
{
    city::IRModule module{"test_return_constant"};
    auto builder = module.CreateBuilder();

    auto function = builder.CreateFunction("test_return_constant");
    builder.SetInsertPoint(function);

    auto return_value = builder.CreateConstant<int>(69);
    builder.InsertRetInst(return_value);

    this->jit.AddIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test_symbol = assembly.Lookup("test_return_constant");
    auto test = test_symbol.ToPointer<int()>();

    ASSERT_EQ(test(), 69);

    this->jit.RemoveModule("test_return_only");
}
