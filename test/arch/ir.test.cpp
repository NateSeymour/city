//
// Created by Nathan Seymour on 6/26/2026.
//
#include <gtest/gtest.h>

#include <city/archc/IR.h>

using namespace city;

TEST(IR, ConstructModule)
{
    Module<IR> module{"test"};

    auto &exit = module.CreateFunction("exit");
    auto &block = exit.GetInsertionBlock();
}