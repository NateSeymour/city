#include <gtest/gtest.h>
#include <ir/Module.h>

TEST(Module, Create)
{
    auto module = city::Module::Create("my_test");
}
