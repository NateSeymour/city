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

TEST_F(Amd64TestRunner, AddConstantFunction)
{
    int const X_VALUE = 69;
    int const Y_VALUE = 420;
    int const EXPECTED_RETURN_VALUE = X_VALUE + Y_VALUE;

    city::IRModule module{"test"};
    auto builder = module.CreateBuilder();

    (void)builder.CreateFunction("add_constants");

    auto retval = builder.InsertAddInst(builder.CreateConstant(X_VALUE), builder.CreateConstant(Y_VALUE));

    builder.InsertRetInst(retval);

    this->jit.InsertIRModule(std::move(module));
    auto assembly = this->jit.CompileAndLink();

    auto test = assembly["add_constants"].ToPointer<int()>();

    ASSERT_EQ(test(), EXPECTED_RETURN_VALUE);

    this->jit.RemoveModule("test");
}
