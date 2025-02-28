#include "jit.test.h"

TEST_F(JITTestRunner, SimpleIfStatement)
{
    /*
     * if (arg[0] > arg[1])
     * {
     *      return 1;
     * }
     * else
     * {
     *      return 0;
     * }
     */
    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        auto test = builder.CreateFunction("test", city::Type::Get<int>(), {2, city::Type::Get<int>()});

        city::Value *lhs = test->GetArgumentValues()[0];
        city::Value *rhs = test->GetArgumentValues()[1];

        city::IRBlock *true_block = builder.CreateCondition(lhs, city::BinaryCondition::GreaterThan, rhs);
    });

    auto test = assembly["test"].ToPointer<int(int, int)>();

    for (int i = 0; i < TEST_ROUNDS; i++)
    {
        auto values = this->GetRandomPair<int>();

        auto value = test(values.first, values.second);
        ASSERT_EQ(value, values.first > values.second);
    }
}
