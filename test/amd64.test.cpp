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
    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    (void)builder.CreateFunction("return_void");
    builder.InsertRetInst(nullptr);

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test = assembly["return_void"].ToPointer<void()>();

    test();

    this->jit.RemoveModule("test");
}

TEST_F(Amd64TestRunner, ReturnConstantFunction)
{
    int const EXPECTED_RETURN_VALUE = 696969;

    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    auto return_type = builder.GetType<int>();
    (void)builder.CreateFunction("return_constant", return_type);

    auto return_value = builder.CreateConstant<int>(EXPECTED_RETURN_VALUE);
    builder.InsertRetInst(return_value);

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test = assembly["return_constant"].ToPointer<int()>();

    ASSERT_EQ(test(), EXPECTED_RETURN_VALUE);

    this->jit.RemoveModule("test");
}

TEST_F(Amd64TestRunner, AddConstantFunction)
{
    int const X_VALUE = 69;
    int const Y_VALUE = 420;
    int const EXPECTED_RETURN_VALUE = X_VALUE + Y_VALUE;

    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    auto return_type = builder.GetType<int>();
    (void)builder.CreateFunction("add_constants", return_type);

    auto x_value = builder.CreateConstant<int>(X_VALUE);
    auto y_value = builder.CreateConstant<int>(Y_VALUE);
    auto return_value = builder.InsertAddInst(x_value, y_value);

    builder.InsertRetInst(return_value->GetReturnValue());

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test = assembly["add_constants"].ToPointer<int()>();

    ASSERT_EQ(test(), EXPECTED_RETURN_VALUE);

    this->jit.RemoveModule("test");
}
