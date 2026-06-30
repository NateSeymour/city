//
// Created by Nathan Seymour on 6/26/2026.
//
#include <gtest/gtest.h>

#include <city/JIT.h>
#include <city/archc/IR.h>

using namespace city;

TEST(IR, ConstructModule)
{
    Module<IR> module{"ConstructModule"};
}

TEST(IR, Addition)
{
    JIT jit;
    Module<IR> module{"Addition"};

    auto &add = module.CreateFunction("add", Type::Get<int>(), {Type::Get<int>(), Type::Get<int>()});
    auto &arguments = add.GetArgumentValues();

    auto &block = add.GetInsertionBlock();
    auto &add_result = block.InsertAdd(arguments[0], arguments[1]);
    (void)block.InsertRet(add_result);


}