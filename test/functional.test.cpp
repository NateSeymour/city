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
    ASSERT_EQ(value, jitstd_pow);
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

TEST_F(JITTestRunner, MultipleFunctionCalls)
{

    int expected_return_value = 0;

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        auto add = builder.CreateFunction("add", city::Type::Get<int>(), {2, city::Type::Get<int>()});
        auto addtmp = builder.InsertAddInst(add->GetArgumentValues()[0], add->GetArgumentValues()[1]);
        builder.InsertRetInst(addtmp);

        auto sub = builder.CreateFunction("sub", city::Type::Get<int>(), {2, city::Type::Get<int>()});
        auto subtmp = builder.InsertSubInst(sub->GetArgumentValues()[0], sub->GetArgumentValues()[1]);
        builder.InsertRetInst(subtmp);

        auto div = builder.CreateFunction("div", city::Type::Get<int>(), {2, city::Type::Get<int>()});
        auto divtmp = builder.InsertDivInst(div->GetArgumentValues()[0], div->GetArgumentValues()[1]);
        builder.InsertRetInst(divtmp);

        auto mul = builder.CreateFunction("mul", city::Type::Get<int>(), {2, city::Type::Get<int>()});
        auto multmp = builder.InsertMulInst(mul->GetArgumentValues()[0], mul->GetArgumentValues()[1]);
        builder.InsertRetInst(multmp);

        std::pair<city::IRFunction *, std::function<int(int, int)>> operations[] = {
                {add, [](int a, int b) { return a + b; }},
                {sub, [](int a, int b) { return a - b; }},
                {div, [](int a, int b) { return a / b; }},
                {mul, [](int a, int b) { return a * b; }},
        };

        (void)builder.CreateFunction("test", city::Type::Get<int>());

        city::Value *last = builder.CreateConstant(expected_return_value);
        for (int i = 0; i < TEST_ROUNDS; i++)
        {
            auto random = this->GetRandomPair<int>();
            auto &op = operations[random.first % 4];

            last = builder.InsertCallInst(op.first, {last, builder.CreateConstant(random.second)});

            expected_return_value = op.second(expected_return_value, random.second);
        }
        builder.InsertRetInst(last);
    });

    auto test = assembly["test"].ToPointer<int()>();
    auto value = test();
    ASSERT_EQ(value, expected_return_value);
}
