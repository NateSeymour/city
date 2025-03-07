#include "city/ir/IRBuilder.h"
#include "city/ir/IRModule.h"
#include "city/value/ConstantValue.h"

using namespace city;

Value *IRBuilder::ReserveValue(Type type)
{
    auto &value = this->module_.values_.emplace_back(std::make_unique<Value>(type));

    return value.get();
}

IRBuilder::IRBuilder(IRModule &module) : module_(module) {}

IRBlock &IRBuilder::InsertBlock()
{
    return *(this->block_ = &this->block_->InsertBlock());
}

void IRBuilder::SetInsertPoint(IRBlock &block) noexcept
{
    this->block_ = &block;
}

void IRBuilder::SetInsertPoint(IRFunction *function) noexcept
{
    if (function == nullptr)
    {
        return;
    }

    this->SetInsertPoint(function->GetLastBlock());
}

IRBlock *IRBuilder::GetInsertPoint() const
{
    return this->block_;
}

IRFunction *IRBuilder::GetInsertFunction() const
{
    return &this->block_->parent_;
}

IRFunction *IRBuilder::CreateFunction(std::string const &name)
{
    return this->CreateFunction(name, Type::Get<void>(), {});
}

IRFunction *IRBuilder::CreateFunction(std::string const &name, Type ret)
{
    return this->CreateFunction(name, ret, {});
}

IRFunction *IRBuilder::CreateFunction(std::string const &name, Type ret, std::vector<Type> const &argument_types)
{
    std::vector<Value *> argument_values;
    argument_values.reserve(argument_types.size());
    for (auto const &type : argument_types)
    {
        argument_values.push_back(this->ReserveValue(type));
    }

    auto [it, _] = this->module_.functions_.insert({name, std::make_unique<IRFunction>(name, ret, argument_types, std::move(argument_values))});
    auto function = it->second.get();

    this->SetInsertPoint(function->GetLastBlock());

    return function;
}

Value *IRBuilder::CreateConstant(Type type, std::vector<std::uint8_t> const &data)
{
    // Append the constant data to the module
    auto &value = this->module_.values_.emplace_back(std::make_unique<ConstantValue>(type, data));

    return value.get();
}

CallInst *IRBuilder::InsertCallInst(Function *function, std::vector<Value *> const &args)
{
    if (this->block_ == nullptr)
    {
        return nullptr;
    }

    return this->block_->InsertInstruction<CallInst>(function, args);
}

RetInst *IRBuilder::InsertRetInst(Value *retval)
{
    if (this->block_ == nullptr)
    {
        return nullptr;
    }

    if (!retval)
    {
        retval = this->ReserveValue(Type::Get<void>());
    }

    return this->block_->InsertInstruction<RetInst>(retval);
}

IRConditionalBlock *IRBuilder::CreateCondition(Value *lhs, BinaryCondition condition, Value *rhs)
{
    return &this->block_->InsertConditionalBlock(lhs, condition, rhs);
}
