#include <city/JIT.h>
#include <city/ir/IRModule.h>
#include <gtest/gtest.h>

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

TEST_F(Amd64TestRunner, ChainedAdditionFunction)
{
    int const X_VALUE = 69;
    int const Y_VALUE = 420;
    int const EXPECTED_RETURN_VALUE = X_VALUE + Y_VALUE + Y_VALUE;

    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    auto return_type = builder.GetType<int>();
    (void)builder.CreateFunction("chained_addition", return_type);

    auto x_value = builder.CreateConstant<int>(X_VALUE);
    auto y_value = builder.CreateConstant<int>(Y_VALUE);

    auto intermediate = builder.InsertAddInst(x_value, y_value);
    auto return_value = builder.InsertAddInst(intermediate->GetReturnValue(), y_value);

    builder.InsertRetInst(return_value->GetReturnValue());

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test = assembly["chained_addition"].ToPointer<int()>();

    ASSERT_EQ(test(), EXPECTED_RETURN_VALUE);

    this->jit.RemoveModule("test");
}

TEST_F(Amd64TestRunner, SubtractConstantFunction)
{
    int const X_VALUE = 69;
    int const Y_VALUE = 420;
    int const EXPECTED_RETURN_VALUE = X_VALUE - Y_VALUE;

    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    auto return_type = builder.GetType<int>();
    (void)builder.CreateFunction("subtract_constants", return_type);

    auto x_value = builder.CreateConstant<int>(X_VALUE);
    auto y_value = builder.CreateConstant<int>(Y_VALUE);
    auto return_value = builder.InsertSubInst(x_value, y_value);

    builder.InsertRetInst(return_value->GetReturnValue());

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test = assembly["subtract_constants"].ToPointer<int()>();

    ASSERT_EQ(test(), EXPECTED_RETURN_VALUE);

    this->jit.RemoveModule("test");
}

TEST_F(Amd64TestRunner, IRFunctionCall)
{
    int const FOO_RET_VALUE = 6969420;
    int const BAR_RET_VALUE = FOO_RET_VALUE + 69;

    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    auto foo = builder.CreateFunction("foo", builder.GetType<int>());
    builder.InsertRetInst(builder.CreateConstant(FOO_RET_VALUE));

    (void)builder.CreateFunction("bar", builder.GetType<int>());
    auto foo_retval = builder.InsertCallInst(foo);
    auto addition = builder.InsertAddInst(foo_retval->GetReturnValue(), builder.CreateConstant(69));
    builder.InsertRetInst(addition->GetReturnValue());

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto bar = assembly["bar"].ToPointer<int()>();

    ASSERT_EQ(bar(), BAR_RET_VALUE);

    this->jit.RemoveModule("test");
}
