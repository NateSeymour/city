#include "IRBuilder.h"
#include "IRModule.h"

using namespace city;

IRBuilder::IRBuilder(IRModule &module) : module_(module) {}

Block *IRBuilder::CreateBlock()
{
    auto &block = this->module_.blocks_.emplace_back(std::make_unique<Block>());
    return block.get();
}

Function *IRBuilder::CreateFunction(std::string name)
{
    return this->CreateFunction(std::move(name), this->GetType<void>(), {});
}

Function *IRBuilder::CreateFunction(std::string name, Type ret)
{
    return this->CreateFunction(std::move(name), ret, {});
}

Function *IRBuilder::CreateFunction(std::string name, Type ret, std::vector<Type> const &args)
{
    auto block = this->CreateBlock();
    auto &function = this->module_.functions_.emplace_back(std::make_unique<Function>(std::move(name), ret, args, block));

    return function.get();
}

void IRBuilder::SetInsertPoint(Block *block) noexcept
{
    this->insert_point_ = block;
}

void IRBuilder::SetInsertPoint(Function *function) noexcept
{
    this->SetInsertPoint(function->blocks_.back());
}

Block *IRBuilder::GetInsertPoint() const noexcept
{
    return this->insert_point_;
}

Value *IRBuilder::CreateConstant(Type type, std::vector<std::byte> const &data)
{
    return this->ReserveLocalValue<Value>(type, data);
}

AddInst *IRBuilder::InsertAddInst(Value *lhs, Value *rhs)
{
    auto lhs_type = lhs->GetType();
    auto rhs_type = rhs->GetType();

    if (lhs_type != rhs_type)
    {
        throw std::runtime_error("incompatible types");
    }

    auto return_value = this->ReserveLocalValue<Value>(lhs_type, StorageClass::Temporary);
    auto addtmp = this->ReserveInstruction<AddInst>(lhs, rhs);
    addtmp->SetReturnValue(return_value);

    return addtmp;
}

StoreInst *IRBuilder::InsertStoreInst(Value *dst, Value *src)
{
    return this->ReserveInstruction<StoreInst>(dst, src);
}

BranchInst *IRBuilder::InsertBranchInst(IRInstruction *target)
{
    return this->ReserveInstruction<BranchInst>(target);
}

RetInst *IRBuilder::InsertRetInst(Value *ret)
{
    return this->ReserveInstruction<RetInst>(ret);
}
