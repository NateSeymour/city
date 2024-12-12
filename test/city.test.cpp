#include <gtest/gtest.h>
#include <ir/Compiler.h>
#include <ir/Module.h>

TEST(City, Module)
{
    city::Module module("test");
    auto builder = module.CreateBuilder();

    auto ret_type = builder.GetBuiltinType<int>();
    auto function = builder.CreateFunction("foo", ret_type);
    builder.SetInsertPoint(function);

    auto ret = builder.CreateConstant<int>(0);
    builder.InsertRetInst(ret);

    city::Compiler compiler;
    compiler.AddModule(module);

    auto assembly = compiler.CompileModules();
    auto foo = assembly.Lookup("foo");
}