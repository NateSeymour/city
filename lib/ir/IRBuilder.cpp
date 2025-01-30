#include <city/ir/IRBuilder.h>
#include <city/ir/IRModule.h>

using namespace city;

ConstantDataContainer *IRBuilder::CreateConstantDataContainer(std::vector<std::byte> const &data)
{
    auto &container = this->module_.global_constants_.emplace_back(std::make_unique<ConstantDataContainer>(data));
    return container.get();
}

Value *IRBuilder::ReserveLocalValue(Type type)
{
    auto &function = this->insert_point_->parent_function_;
    auto &locals = function.local_values_;
    auto &value = locals.emplace_back(std::make_unique<Value>(type));

    return value.get();
}

IRBuilder::IRBuilder(IRModule &module) : module_(module) {}

IRBlock &IRBuilder::CreateBlock()
{
    auto &insert_function = this->insert_point_->parent_function_;
    return insert_function.AppendBlock();
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
    auto [it, _] = this->module_.functions_.insert({name, std::make_unique<IRFunction>(name, ret, args)});
    auto function = it->second.get();

    this->SetInsertPoint(function->GetLastBlock());

    return function;
}

void IRBuilder::SetInsertPoint(IRBlock &block) noexcept
{
    this->insert_point_ = &block;
}

void IRBuilder::SetInsertPoint(IRFunction *function) noexcept
{
    this->SetInsertPoint(function->GetLastBlock());
}

IRBlock &IRBuilder::GetInsertPoint() const
{
    return *this->insert_point_;
}

Value *IRBuilder::CreateConstant(Type type, std::vector<std::byte> const &data)
{
    auto container = this->CreateConstantDataContainer(data);
    auto value = this->ReserveLocalValue(type);

    value->AssociateContainer(container);
    container->AssociateValue(value);

    return value;
}

AddInst *IRBuilder::InsertAddInst(Value *lhs, Value *rhs)
{
    auto lhs_type = lhs->GetType();
    auto rhs_type = rhs->GetType();

    if (lhs_type != rhs_type)
    {
        throw std::runtime_error("incompatible types");
    }

    auto return_value = this->ReserveLocalValue(lhs_type);
    auto addtmp = this->ReserveInstruction<AddInst>(return_value, lhs, rhs);

    return addtmp;
}

SubInst *IRBuilder::InsertSubInst(Value *lhs, Value *rhs)
{
    auto lhs_type = lhs->GetType();
    auto rhs_type = rhs->GetType();

    if (lhs_type != rhs_type)
    {
        throw std::runtime_error("incompatible types");
    }

    auto return_value = this->ReserveLocalValue(lhs_type);
    auto subtmp = this->ReserveInstruction<SubInst>(return_value, lhs, rhs);

    return subtmp;
}

FAddInst *IRBuilder::InsertFAddInst(Value *lhs, Value *rhs)
{
    auto lhs_type = lhs->GetType();
    auto rhs_type = rhs->GetType();

    if (lhs_type != rhs_type)
    {
        throw std::runtime_error("incompatible types");
    }

    auto return_value = this->ReserveLocalValue(lhs_type);
    auto faddtmp = this->ReserveInstruction<FAddInst>(return_value, lhs, rhs);

    return faddtmp;
}

CallInst *IRBuilder::InsertCallInst(IRFunction *function)
{
    auto return_value = this->ReserveLocalValue(function->ret_type_);
    return this->ReserveInstruction<CallInst>(return_value, function);
}

RetInst *IRBuilder::InsertRetInst(Value *return_value)
{
    if (!return_value)
    {
        return_value = this->ReserveLocalValue(this->GetType<void>());
    }

    return this->ReserveInstruction<RetInst>(return_value);
}
