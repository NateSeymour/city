#include "Builder.h"
#include "Module.h"

using namespace city;

Builder::Builder(Module &module) : module_(module) {}

Block *Builder::CreateBlock()
{
    auto &block = this->module_.blocks_.emplace_back(std::make_unique<Block>());
    return block.get();
}

Function *Builder::CreateFunction(std::string name)
{
    return this->CreateFunction(std::move(name), this->GetType<void>(), {});
}

Function *Builder::CreateFunction(std::string name, Type ret)
{
    return this->CreateFunction(std::move(name), ret, {});
}

Function *Builder::CreateFunction(std::string name, Type ret, std::vector<Type> const &args)
{
    auto block = this->CreateBlock();
    auto &function = this->module_.functions_.emplace_back(std::make_unique<Function>(std::move(name), ret, args, block));

    return function.get();
}

void Builder::SetInsertPoint(Block *block) noexcept
{
    this->insert_point_ = block;
}

void Builder::SetInsertPoint(Function *function) noexcept
{
    // this->SetInsertPoint(function->body_);
}

Block *Builder::GetInsertPoint() const noexcept
{
    return this->insert_point_;
}

ConstantValue *Builder::CreateConstant(Type type, std::vector<std::byte> const &data)
{
    return this->ReserveLocalValue<ConstantValue>(type, data);
}

Value *Builder::CreateStackAlloc(Type type)
{
    return this->ReserveLocalValue<Value>(type, StorageClass::StackPreferred);
}

Value *Builder::CreateHeapAlloc(Type type)
{
    return this->ReserveLocalValue<Value>(type, StorageClass::HeapPreferred);
}

AddInst *Builder::InsertAddInst(Value *lhs, Value *rhs)
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

StoreInst *Builder::InsertStoreInst(Value *dst, Value *src)
{
    return this->ReserveInstruction<StoreInst>(dst, src);
}

BranchInst *Builder::InsertBranchInst(IRInstruction *target)
{
    return this->ReserveInstruction<BranchInst>(target);
}

RetInst *Builder::InsertRetInst(Value *ret)
{
    return this->ReserveInstruction<RetInst>(ret);
}
