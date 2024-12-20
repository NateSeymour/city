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

TEST_F(Amd64TestRunner, ReturnOnlyFunction)
{
    city::IRModule module{"test_return_only"};
    auto builder = module.CreateBuilder();

    auto function = builder.CreateFunction("test");
    builder.SetInsertPoint(function);

    builder.InsertRetInst(nullptr);

    this->jit.AddIRModule(std::move(module));
    auto assembly = this->jit.CompileModules();

    auto test_symbol = assembly.Lookup("test");
    auto test = test_symbol.ToPointer<void()>();

    test();

    this->jit.RemoveModule("test_return_only");
}
