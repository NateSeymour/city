#include "IRBuilder.h"
#include "IRModule.h"
#include "value/ConstantValue.h"

using namespace city;

IRBuilder::IRBuilder(IRModule &module) : module_(module) {}

IRBlock *IRBuilder::CreateBlock()
{
    auto insert_function = this->insert_point_->parent_function_;
    auto &block = this->module_.blocks_.emplace_back(std::make_unique<IRBlock>(insert_function));
    return block.get();
}

IRFunction *IRBuilder::CreateFunction(std::string const &name)
{
    return this->CreateFunction(name, this->GetType<void>(), {});
}

IRFunction *IRBuilder::CreateFunction(std::string const &name, Type ret)
{
    return this->CreateFunction(name, ret, {});
}

IRFunction *IRBuilder::CreateFunction(std::string const &name, Type ret, std::vector<Type> const &args)
{
    auto block = this->CreateBlock();
    auto [it, _] = this->module_.functions_.insert({name, std::make_unique<IRFunction>(ret, args, block)});

    return it->second.get();
}

void IRBuilder::SetInsertPoint(IRBlock *block) noexcept
{
    this->insert_point_ = block;
}

void IRBuilder::SetInsertPoint(IRFunction *function) noexcept
{
    this->SetInsertPoint(function->blocks_.back());
}

IRBlock *IRBuilder::GetInsertPoint() const noexcept
{
    return this->insert_point_;
}

Value *IRBuilder::CreateConstant(Type type, std::vector<std::byte> const &data)
{
    return this->ReserveLocalValue<ConstantValue>(type, data);
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