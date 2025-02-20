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

TEST_F(JITTestRunner, Int16Addition)
{
    auto values = this->GetRandomPair<std::uint16_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("add");

        auto retval = builder.InsertAddInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["add"].ToPointer<std::uint16_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first + values.second);
}

TEST_F(JITTestRunner, Int32Addition)
{
    auto values = this->GetRandomPair<std::uint32_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("add");

        auto retval = builder.InsertAddInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["add"].ToPointer<std::uint32_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first + values.second);
}

TEST_F(JITTestRunner, Int64Addition)
{
    auto values = this->GetRandomPair<std::uint64_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("add");

        auto retval = builder.InsertAddInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["add"].ToPointer<std::uint64_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first + values.second);
}

TEST_F(JITTestRunner, FP32Addition)
{
    auto values = this->GetRandomPair<float>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("add");

        auto retval = builder.InsertAddInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["add"].ToPointer<float()>();

    auto value = test();
    ASSERT_EQ(value, values.first + values.second);
}

TEST_F(JITTestRunner, FP64Addition)
{
    auto values = this->GetRandomPair<double>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("add");

        auto retval = builder.InsertAddInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["add"].ToPointer<double()>();

    auto value = test();
    ASSERT_EQ(value, values.first + values.second);
}

TEST_F(JITTestRunner, Int16Subtraction)
{
    auto values = this->GetRandomPair<std::uint16_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("sub");

        auto retval = builder.InsertSubInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["sub"].ToPointer<std::uint16_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first - values.second);
}

TEST_F(JITTestRunner, Int32Subtraction)
{
    auto values = this->GetRandomPair<std::uint32_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("sub");

        auto retval = builder.InsertSubInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["sub"].ToPointer<std::uint32_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first - values.second);
}

TEST_F(JITTestRunner, Int64Subtraction)
{
    auto values = this->GetRandomPair<std::uint64_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("sub");

        auto retval = builder.InsertSubInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["sub"].ToPointer<std::uint64_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first - values.second);
}

TEST_F(JITTestRunner, FP32Subtraction)
{
    auto values = this->GetRandomPair<float>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("sub");

        auto retval = builder.InsertSubInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["sub"].ToPointer<float()>();

    auto value = test();
    ASSERT_EQ(value, values.first - values.second);
}

TEST_F(JITTestRunner, FP64Subtraction)
{
    auto values = this->GetRandomPair<double>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("sub");

        auto retval = builder.InsertSubInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["sub"].ToPointer<double()>();

    auto value = test();
    ASSERT_EQ(value, values.first - values.second);
}

TEST_F(JITTestRunner, Int16Division)
{
    auto values = this->GetRandomPair<std::uint16_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("div");

        auto retval = builder.InsertDivInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["div"].ToPointer<std::uint16_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first / values.second);
}

TEST_F(JITTestRunner, Int32Division)
{
    auto values = this->GetRandomPair<std::uint32_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("div");

        auto retval = builder.InsertDivInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["div"].ToPointer<std::uint32_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first / values.second);
}

TEST_F(JITTestRunner, Int64Division)
{
    auto values = this->GetRandomPair<std::uint64_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("div");

        auto retval = builder.InsertDivInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["div"].ToPointer<std::uint64_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first / values.second);
}

TEST_F(JITTestRunner, FP32Division)
{
    auto values = this->GetRandomPair<float>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("div");

        auto retval = builder.InsertDivInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["div"].ToPointer<float()>();

    auto value = test();
    ASSERT_EQ(value, values.first / values.second);
}

TEST_F(JITTestRunner, FP64Division)
{
    auto values = this->GetRandomPair<double>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("div");

        auto retval = builder.InsertDivInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["div"].ToPointer<double()>();

    auto value = test();
    ASSERT_EQ(value, values.first / values.second);
}

TEST_F(JITTestRunner, Int16Multiplication)
{
    auto values = this->GetRandomPair<std::uint16_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("mul");

        auto retval = builder.InsertMulInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["mul"].ToPointer<std::uint16_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first * values.second);
}

TEST_F(JITTestRunner, Int32Multiplication)
{
    auto values = this->GetRandomPair<std::uint32_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("mul");

        auto retval = builder.InsertMulInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["mul"].ToPointer<std::uint32_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first * values.second);
}

TEST_F(JITTestRunner, Int64Multiplication)
{
    auto values = this->GetRandomPair<std::uint64_t>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("mul");

        auto retval = builder.InsertMulInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["mul"].ToPointer<std::uint64_t()>();

    auto value = test();
    ASSERT_EQ(value, values.first * values.second);
}

TEST_F(JITTestRunner, FP32Multiplication)
{
    auto values = this->GetRandomPair<float>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("mul");

        auto retval = builder.InsertMulInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["mul"].ToPointer<float()>();

    auto value = test();
    ASSERT_EQ(value, values.first * values.second);
}

TEST_F(JITTestRunner, FP64Multiplication)
{
    auto values = this->GetRandomPair<double>();

    auto assembly = this->BuildTestModule([&](city::IRBuilder &builder) {
        (void)builder.CreateFunction("mul");

        auto retval = builder.InsertMulInst(builder.CreateConstant(values.first), builder.CreateConstant(values.second));

        builder.InsertRetInst(retval);
    });

    auto test = assembly["mul"].ToPointer<double()>();

    auto value = test();
    ASSERT_EQ(value, values.first * values.second);
}

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
