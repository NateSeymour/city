#include <gtest/gtest.h>
#include <ir/JIT.h>
#include <ir/Module.h>

TEST(City, Module)
{
    auto module = city::Module::Create("my_test");
    auto builder = module->CreateBuilder();

    /*
     * Add some IR
     */

    city::JIT compiler;
    compiler.AddModule(std::move(module));
    auto assembly = compiler.CompileModules();
}
