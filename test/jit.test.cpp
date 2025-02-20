#include <array>
#include <city/JIT.h>
#include <city/ir/IRModule.h>
#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

namespace tstd
{
    extern "C" double my_pow(double a, double b)
    {
        return std::pow(a, b);
    }
} // namespace tstd

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

    void SetUp() override
    {
        std::srand(std::time({}));

        city::InterfaceModule module{"__std"};

        std::array functions = {
                module.InsertBinding("__pow", tstd::my_pow),
        };

        for (auto function : functions)
        {
            this->stdlib[*function->GetName()] = function;
        }

        this->jit.InsertInterfaceModule(std::move(module));
    }

    void TearDown() override {}
};

template<typename T>
T add(T a, T b)
{
    return a + b;
}

template<typename T>
T sub(T a, T b)
{
    return a - b;
}

template<typename T>
T mul(T a, T b)
{
    return a * b;
}

template<typename T>
T div(T a, T b)
{
    return a / b;
}

TEST_F(JITTestRunner, Int16Addition)
{
    this->TestBinOp<std::int16_t>("add_int16", &city::IRBuilder::InsertAddInst, add<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Addition)
{
    this->TestBinOp<std::uint16_t>("add_uint16", &city::IRBuilder::InsertAddInst, add<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Addition)
{
    this->TestBinOp<std::int32_t>("add_int32", &city::IRBuilder::InsertAddInst, add<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Addition)
{
    this->TestBinOp<std::uint32_t>("add_uint32", &city::IRBuilder::InsertAddInst, add<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Addition)
{
    this->TestBinOp<std::int64_t>("add_int64", &city::IRBuilder::InsertAddInst, add<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Addition)
{
    this->TestBinOp<std::uint64_t>("add_uint64", &city::IRBuilder::InsertAddInst, add<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Addition)
{
    this->TestBinOp<float>("add_fp32", &city::IRBuilder::InsertAddInst, add<float>);
}

TEST_F(JITTestRunner, FP64Addition)
{
    this->TestBinOp<double>("add_fp64", &city::IRBuilder::InsertAddInst, add<double>);
}

TEST_F(JITTestRunner, Int16Subtraction)
{
    this->TestBinOp<std::int16_t>("sub_int16", &city::IRBuilder::InsertSubInst, sub<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Subtraction)
{
    this->TestBinOp<std::uint16_t>("sub_uint16", &city::IRBuilder::InsertSubInst, sub<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Subtraction)
{
    this->TestBinOp<std::int32_t>("sub_int32", &city::IRBuilder::InsertSubInst, sub<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Subtraction)
{
    this->TestBinOp<std::uint32_t>("sub_uint32", &city::IRBuilder::InsertSubInst, sub<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Subtraction)
{
    this->TestBinOp<std::int64_t>("sub_int64", &city::IRBuilder::InsertSubInst, sub<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Subtraction)
{
    this->TestBinOp<std::uint64_t>("sub_uint64", &city::IRBuilder::InsertSubInst, sub<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Subtraction)
{
    this->TestBinOp<float>("sub_fp32", &city::IRBuilder::InsertSubInst, sub<float>);
}

TEST_F(JITTestRunner, FP64Subtraction)
{
    this->TestBinOp<double>("sub_fp64", &city::IRBuilder::InsertSubInst, sub<double>);
}

TEST_F(JITTestRunner, Int16Multiplication)
{
    this->TestBinOp<std::int16_t>("mul_int16", &city::IRBuilder::InsertMulInst, mul<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Multiplication)
{
    this->TestBinOp<std::uint16_t>("mul_uint16", &city::IRBuilder::InsertMulInst, mul<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Multiplication)
{
    this->TestBinOp<std::int32_t>("mul_int32", &city::IRBuilder::InsertMulInst, mul<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Multiplication)
{
    this->TestBinOp<std::uint32_t>("mul_uint32", &city::IRBuilder::InsertMulInst, mul<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Multiplication)
{
    this->TestBinOp<std::int64_t>("mul_int64", &city::IRBuilder::InsertMulInst, mul<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Multiplication)
{
    this->TestBinOp<std::uint64_t>("mul_uint64", &city::IRBuilder::InsertMulInst, mul<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Multiplication)
{
    this->TestBinOp<float>("mul_fp32", &city::IRBuilder::InsertMulInst, mul<float>);
}

TEST_F(JITTestRunner, FP64Multiplication)
{
    this->TestBinOp<double>("mul_fp64", &city::IRBuilder::InsertMulInst, mul<double>);
}

TEST_F(JITTestRunner, Int16Division)
{
    this->TestBinOp<std::int16_t>("div_int16", &city::IRBuilder::InsertDivInst, div<std::int16_t>);
}

TEST_F(JITTestRunner, UInt16Division)
{
    this->TestBinOp<std::uint16_t>("div_uint16", &city::IRBuilder::InsertDivInst, div<std::uint16_t>);
}

TEST_F(JITTestRunner, Int32Division)
{
    this->TestBinOp<std::int32_t>("div_int32", &city::IRBuilder::InsertDivInst, div<std::int32_t>);
}

TEST_F(JITTestRunner, UInt32Division)
{
    this->TestBinOp<std::uint32_t>("div_uint32", &city::IRBuilder::InsertDivInst, div<std::uint32_t>);
}

TEST_F(JITTestRunner, Int64Division)
{
    this->TestBinOp<std::int64_t>("div_int64", &city::IRBuilder::InsertDivInst, div<std::int64_t>);
}

TEST_F(JITTestRunner, UInt64Division)
{
    this->TestBinOp<std::uint64_t>("div_uint64", &city::IRBuilder::InsertDivInst, div<std::uint64_t>);
}

TEST_F(JITTestRunner, FP32Division)
{
    this->TestBinOp<float>("div_fp32", &city::IRBuilder::InsertDivInst, div<float>);
}

TEST_F(JITTestRunner, FP64Division)
{
    this->TestBinOp<double>("div_fp64", &city::IRBuilder::InsertDivInst, div<double>);
}

/*
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
    ASSERT_EQ(value, tstd::my_pow(values.first, values.second));
}
*/
