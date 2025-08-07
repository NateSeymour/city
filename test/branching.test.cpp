#include "jit.test.h"

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
TEST_F(JITTestRunner, SimpleIfStatement)
{

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        auto test = builder.CreateFunction("test", city::Type::Get<int>(), {2, city::Type::Get<int>()});

        city::Value *lhs = test->GetArgumentValues()[0];
        city::Value *rhs = test->GetArgumentValues()[1];

        city::IRConditionalBlock *condition = builder.CreateCondition(lhs, city::BinaryCondition::GreaterThan, rhs);

        builder.SetInsertPoint(condition->GetTrueBlock());
        builder.InsertRetInst(builder.CreateConstant(1));

        builder.SetInsertPoint(condition->GetElseBlock());
        builder.InsertRetInst(builder.CreateConstant(0));

        builder.InsertBlock();
        builder.InsertRetInst(builder.CreateConstant(-1));
    });

    auto test = assembly["test"].ToPointer<int(int, int)>();

    for (int i = 0; i < TEST_ROUNDS; i++)
    {
        auto values = this->GetRandomPair<int>();

        auto value = test(values.first, values.second);
        ASSERT_EQ(value, values.first > values.second);
    }
}

/*
 * int strcmp(char const *a, char const *b)
 * {
 *      int i = 0;
 *      while (a[i] != '\0' && b[i] != '\0')
 *      {
 *          int diff = a[i] - b[i];
 *          if (diff)
 *          {
 *              return diff;
 *          }
 *
 *          i++;
 *      }
 *
 *      return 0;
 * }
 */
/*
TEST_F(JITTestRunner, StringComparison)
{
    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        auto test = builder.CreateFunction("test", city::Type::Get<int>(), {2, city::Type::Get<char const *>()});

        city::Value *lhs = test->GetArgumentValues()[0];
        city::Value *rhs = test->GetArgumentValues()[1];

        city::Value *i = builder.CreateConstant(-1);

        city::IRBlock &loop_begin = builder.InsertBlock();
        city::Value *a_i = builder.CreatePDerefInst<char const>(lhs, i);
        city::Value *b_i = builder.CreatePDerefInst<char const>(rhs, i);

        city::Value *sum = builder.InsertAddInst(a_i, b_i);
        city::IRConditionalBlock *cond = builder.CreateCondition(sum, city::BinaryCondition::EqualTo, builder.CreateConstant(0));

        builder.SetInsertPoint(cond->GetTrueBlock());
        city::Value *diff = builder.InsertSubInst(a_i, b_i);
        builder.InsertBranchInst(loop_begin);

        builder.SetInsertPoint(cond->GetElseBlock());
        builder.InsertRetInst(builder.CreateConstant(0));
    });

    auto test = assembly["test"].ToPointer<int(int, int)>();

    for (int i = 0; i < TEST_ROUNDS; i++)
    {
        auto values = this->GetRandomPair<int>();

        auto value = test(values.first, values.second);
        ASSERT_EQ(value, values.first > values.second);
    }
}
*/