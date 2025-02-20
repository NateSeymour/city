#include "jit.test.h"

TEST_F(JITTestRunner, FunctionCall)
{
    auto values = this->GetRandomPair<double>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        auto callee = builder.CreateFunction("foo", city::Type::Get<double>());
        builder.InsertRetInst(builder.CreateConstant(values.first));

        (void)builder.CreateFunction("bar", city::Type::Get<double>());
        auto retval = builder.InsertCallInst(callee);
        auto multmp = builder.InsertMulInst(retval, builder.CreateConstant(values.second));
        builder.InsertRetInst(multmp);
    });

    auto test = assembly["bar"].ToPointer<double()>();

    auto value = test();
    ASSERT_EQ(value, values.first * values.second);
}

TEST_F(JITTestRunner, ReturnFunctionPointer)
{
    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("test", city::Type::Get<void *>());
        builder.InsertRetInst(this->stdlib["__pow"]);
    });

    auto test = assembly["test"].ToPointer<void *()>();

    auto value = test();
    ASSERT_EQ(value, reinterpret_cast<void *>((double (*)(double, double))std::pow));
}

TEST_F(JITTestRunner, InterfaceFunctionCall)
{
    auto values = this->GetRandomPair<double>();
    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("test", city::Type::Get<double>(), {2, city::Type::Get<double>()});

        auto pow = builder.InsertCallInst(this->stdlib["__pow"], {builder.CreateConstant(values.first), builder.CreateConstant(values.second)});

        builder.InsertRetInst(pow);
    });

    auto test = assembly["test"].ToPointer<double(double, double)>();

    auto value = test(values.first, values.second);
    ASSERT_EQ(value, jitstd_pow(values.first, values.second));
}
