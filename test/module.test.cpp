#include <city/interface/InterfaceModule.h>
#include <city/ir/IRModule.h>
#include <cmath>
#include <gtest/gtest.h>

TEST(IRModule, Create)
{
    city::IRModule module{"test"};
}

TEST(InterfaceModule, Create)
{
    city::InterfaceModule module{"test"};
}

void test() {}

TEST(InterfaceModule, InsertBinding)
{
    city::InterfaceModule module{"test"};

    auto sqrt = module.InsertBinding("sqrt", (double (*)(double))std::sqrt);
    auto pow = module.InsertBinding("pow", (double (*)(double, double))std::pow);
    auto testfn = module.InsertBinding("test", test);
}
