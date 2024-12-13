#include <JIT.h>
#include <gtest/gtest.h>
#include <ir/Module.h>

class Amd64TestRunner : public testing::Test
{
protected:
    city::JIT jit;

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(Amd64TestRunner, ReturnOnlyFunction)
{
    auto module = city::Module::Create("test_return_only");
    auto builder = module->CreateBuilder();

    auto function = builder.CreateFunction("test");
    builder.SetInsertPoint(function);

    builder.InsertRetInst(nullptr);

    this->jit.AddModule(std::move(module));
    auto assembly = this->jit.CompileModules();

    this->jit.RemoveModule("test_return_only");
}
