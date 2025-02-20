#ifndef JIT_TEST_H
#define JIT_TEST_H

#include <array>
#include <city/JIT.h>
#include <city/ir/IRModule.h>
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

extern "C"
{
    double jitstd_pow(double a, double b);
}

class JITTestRunner : public testing::Test
{
protected:
    static constexpr int TEST_ROUNDS = 1000;

    city::JIT jit;

    std::unordered_map<std::string, city::Function *> stdlib;

    template<typename T>
    [[nodiscard]] std::pair<T, T> GetRandomPair() const
    {
        return {
                static_cast<T>(std::rand()) + (static_cast<T>(std::rand()) / RAND_MAX),
                static_cast<T>(std::rand()) + (static_cast<T>(std::rand()) / RAND_MAX),
        };
    }

    [[nodiscard]] city::Assembly BuildTestModule(std::function<void(city::IRBuilder &)> constructor)
    {
        city::IRModule module{"test"};
        auto builder = module.CreateBuilder();

        constructor(builder);

        this->jit.InsertIRModule(std::move(module));

        auto assembly = this->jit.Link();

        this->jit.RemoveModule("test");

        return std::move(assembly);
    }

    template<typename OperandType, typename BuilderFunctionType, typename VerificationType>
    void TestBinOp(char const *opname, BuilderFunctionType builder_fn, VerificationType verify)
    {
        for (int i = 0; i < TEST_ROUNDS; i++)
        {
            auto values = this->GetRandomPair<OperandType>();

            auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
                (void)builder.CreateFunction(opname, city::Type::Get<OperandType>());

                city::Value *lhs = builder.CreateConstant(values.first);
                city::Value *rhs = builder.CreateConstant(values.second);
                auto tmp = (builder.*builder_fn)(lhs, rhs);

                builder.InsertRetInst(tmp);
            });

            auto test = assembly[opname].template ToPointer<OperandType()>();

            auto value = test();
            ASSERT_EQ(value, verify(values.first, values.second));
        }
    }

    template<typename OperandType, typename BuilderFunctionType, typename VerificationType>
    void TestBinOpArgs(char const *opname, BuilderFunctionType builder_fn, VerificationType verify)
    {
        auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
            std::vector<city::Type> arg_types{2, city::Type::Get<OperandType>()};
            auto fn = builder.CreateFunction(opname, city::Type::Get<OperandType>(), arg_types);

            auto tmp = (builder.*builder_fn)(fn->GetArgumentValues()[0], fn->GetArgumentValues()[1]);

            builder.InsertRetInst(tmp);
        });

        auto test = assembly[opname].template ToPointer<OperandType(OperandType, OperandType)>();
        for (int i = 0; i < TEST_ROUNDS; i++)
        {
            auto values = this->GetRandomPair<OperandType>();

            auto value = test(values.first, values.second);
            ASSERT_EQ(value, verify(values.first, values.second));
        }
    }

    void SetUp() override
    {
        std::srand(std::time({}));

        city::InterfaceModule module{"__std"};

        std::array functions = {
                module.InsertBinding("__pow", jitstd_pow),
        };

        for (auto function : functions)
        {
            this->stdlib[*function->GetName()] = function;
        }

        this->jit.InsertInterfaceModule(std::move(module));
    }

    void TearDown() override {}
};

#endif // JIT_TEST_H
