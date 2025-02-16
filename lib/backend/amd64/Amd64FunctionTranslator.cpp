#include "city/backend/amd64/Amd64FunctionTranslator.h"
#include "city/JIT.h"
#include "city/container/StackAllocationContainer.h"

#include "city/backend/amd64/instruction/arithmetic/Amd64Add.h"
#include "city/backend/amd64/instruction/arithmetic/Amd64Div.h"
#include "city/backend/amd64/instruction/arithmetic/Amd64Mul.h"
#include "city/backend/amd64/instruction/arithmetic/Amd64Sub.h"
#include "city/backend/amd64/instruction/control/Amd64Call.h"
#include "city/backend/amd64/instruction/control/Amd64Leave.h"
#include "city/backend/amd64/instruction/control/Amd64Ret.h"
#include "city/backend/amd64/instruction/memory/Amd64Mov.h"
#include "city/backend/amd64/instruction/memory/Amd64Push.h"

using namespace city;

void Amd64FunctionTranslator::TranslateInstruction(AddInst &inst)
{
    this->TranslateBinaryInstruction<AddInst, Amd64Add>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(DivInst &inst)
{
    this->TranslateBinaryInstruction<DivInst, Amd64Div>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(MulInst &inst)
{
    this->TranslateBinaryInstruction<MulInst, Amd64Mul>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(SubInst &inst)
{
    this->TranslateBinaryInstruction<SubInst, Amd64Sub>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(CallInst &inst)
{
    // Generate address stub
    auto &address_reg = this->AcquireGPRegister();

    Stub stub{
            .label = inst.GetTarget()->GetName(),
            .type = StubSourceLocation::Text,
    };
    this->Insert(Amd64Mov::OIS(address_reg, std::move(stub)));

    // Persist volatile registers
    for (auto &reg : this->registers.r)
    {
        if (reg.HasValue() && reg.GetValue()->IsUsed())
        {
            auto &swap = this->AcquireStackSpace(reg.GetSize());
            this->MoveValue(swap, reg);
        }
    }

    for (auto &reg : this->registers.xmm)
    {
        if (reg.HasValue() && reg.GetValue()->IsUsed())
        {
            auto &swap = this->AcquireStackSpace(reg.GetSize());
            this->MoveValue(swap, reg);
        }
    }

    // Load arguments
    auto const &args = inst.GetArguments();
    for (int i = 0; i < args.size(); i++)
    {
        auto value = args[i];
        auto const &value_type = value->GetType();

        if (!value->IsInstantiated())
        {
            throw std::runtime_error("attempted to pass uninstantiated value");
        }

        auto container = value->GetContainer();
        if (value_type.GetNativeType() == NativeType::Integer)
        {
            container->Load(*this, *this->registers.r_args[i]);
        }
        else if (value_type.GetNativeType() == NativeType::FloatingPoint)
        {
            container->Load(*this, *this->registers.xmm_args[i]);
        }
    }

    // Make call
    this->Insert(Amd64Call::M64(address_reg));

    // Instantiate retval
    auto native_type = inst.GetType().GetNativeType();
    if (native_type == NativeType::Integer)
    {
        this->registers.r[0].InstantiateValue(&inst);
    }
    else if (native_type == NativeType::FloatingPoint)
    {
        this->registers.xmm[0].InstantiateValue(&inst);
    }
}

void Amd64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto retval = inst.GetReturnValue();
    if (retval && retval->IsInstantiated())
    {
        auto native_type = inst.GetType().GetNativeType();
        if (native_type == NativeType::Integer)
        {
            this->MoveValue(this->registers.r[0], *retval, ConflictStrategy::Discard);
        }
        else if (native_type == NativeType::FloatingPoint)
        {
            this->MoveValue(this->registers.xmm[0], *retval, ConflictStrategy::Discard);
        }
    }

    if (this->stack_depth_ > 0)
    {
        this->Insert(Amd64Leave::ZO());
    }

    this->Insert(Amd64Ret::ZONear());
}

Register &Amd64FunctionTranslator::PrepareDestinationValue(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot prepare uninstantiated value");
    }

    Container *container = value.GetContainer();

    // If this is the last read then we can store the new value there.
    if (container->GetType() == ContainerType::Register && value.GetReadCount() == 1)
    {
        return *dynamic_cast<Register *>(container);
    }

    // Otherwise it needs to be copied into a new register.
    return this->CopyValue(value);
}

std::tuple<Register &, Amd64Mod, std::int32_t> Amd64FunctionTranslator::PrepareSourceValue(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot prepare uninstantiated value");
    }

    Container *container = value.GetContainer();

    switch (container->GetType())
    {
        case ContainerType::Constant:
        {
            return {this->CopyValue(value), Amd64Mod::Value, 0};
        }

        case ContainerType::StackAllocation:
        {
            auto stack_allocation = dynamic_cast<StackAllocationContainer *>(container);
            return {this->registers.r[5], Amd64Mod::DisplacedPointer, stack_allocation->GetOffset() * -1};
        }

        case ContainerType::Register:
        {
            return {*dynamic_cast<Register *>(container), Amd64Mod::Value, 0};
        }
    }
}

void Amd64FunctionTranslator::Load(Register &dst, ConstantDataContainer &src)
{
    if (src.GetSize() > 8)
    {
        throw std::runtime_error("value is too big");
    }

    auto value_type = src.GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->Insert(Amd64Mov::OIX(dst, src.GetDataBuffer()));
        this->Insert(Amd64Mov::RMX(dst, dst, dst.GetSize(), Amd64Mod::Pointer));
    }
    // Need to take the roundabout way of loading the value first onto the stack via integer move and then into an xmm register.
    else if (value_type.GetNativeType() == NativeType::FloatingPoint)
    {
        auto &valtmp = this->AcquireGPRegister(RegisterType::Integer);
        auto &stacktmp = this->AcquireStackSpace(8);

        this->Insert(Amd64Mov::OIX(valtmp, src.GetDataBuffer()));
        this->Insert(Amd64Mov::MR64(this->registers.r[5], valtmp, Amd64Mod::DisplacedPointer, stacktmp.GetOffset() * -1));
        this->Insert(Amd64Mov::SDA(dst, this->registers.r[5], Amd64Mod::DisplacedPointer, stacktmp.GetOffset() * -1));
    }
}

void Amd64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src)
{
    auto &rbp = this->registers.r[5];

    if (dst.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::RMX(dst, rbp, src.GetSize(), Amd64Mod::DisplacedPointer, src.GetOffset() * -1));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, rbp, Amd64Mod::DisplacedPointer, src.GetOffset() * -1));
    }
}

void Amd64FunctionTranslator::Load(Register &dst, Register &src)
{
    // Return if attempt to load into the same register.
    if (dst.GetCode() == src.GetCode())
    {
        return;
    }

    if (dst.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::RM64(dst, src));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, src));
    }
}

void Amd64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src)
{
    auto &rbp = this->registers.r[5];

    if (src.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::MR64(rbp, src, Amd64Mod::DisplacedPointer, dst.GetOffset() * -1));
    }
    else if (src.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(rbp, src, Amd64Mod::DisplacedPointer, dst.GetOffset() * -1));
    }
}

void Amd64FunctionTranslator::Store(Register &dst, Register &src)
{
    this->Load(dst, src);
}

Register &Amd64FunctionTranslator::CopyValue(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("impossible to copy uninstantiated value");
    }

    auto value_type = value.GetType();
    auto register_type = value_type.GetNativeType() == NativeType::Integer ? RegisterType::Integer : RegisterType::FloatingPoint;
    auto &target_register = this->AcquireGPRegister(register_type);

    auto src = value.GetContainer();
    src->Load(*this, target_register);
    target_register.InstantiateValue(&value);

    return target_register;
}

void Amd64FunctionTranslator::MoveValue(StackAllocationContainer &dst, Register &src)
{
    if (!src.HasValue())
    {
        throw std::runtime_error("source has no value to move");
    }

    if (dst.HasValue() && dst.GetValue()->IsUsed())
    {
        throw std::runtime_error("unresolvable value conflict");
    }

    this->Store(dst, src);

    dst.TakeValue(&src);
}

void Amd64FunctionTranslator::MoveValue(Register &dst, Register &src, ConflictStrategy strategy)
{
    if (!src.HasValue())
    {
        throw std::runtime_error("source has no value to move");
    }

    this->HandleConflict(dst, strategy);

    this->Store(dst, src);

    dst.TakeValue(&src);
}

void Amd64FunctionTranslator::MoveValue(Register &dst, Value &value, ConflictStrategy strategy)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot move uninstantiated value");
    }

    this->HandleConflict(dst, strategy);

    auto &src = *value.GetContainer();
    src.Load(*this, dst);

    dst.TakeValue(&src);
}

void Amd64FunctionTranslator::HandleConflict(Register &reg, ConflictStrategy strategy)
{
    if (!reg.HasValue())
    {
        return;
    }

    auto value = reg.GetValue();
    if (!value->IsUsed())
    {
        return;
    }

    switch (strategy)
    {
        case ConflictStrategy::Discard:
        {
            return;
        }

        case ConflictStrategy::Save:
        {
            auto &swap = this->AcquireStackSpace(reg.GetSize());
            this->MoveValue(swap, reg);
            break;
        }
    }
}

Register &Amd64FunctionTranslator::AcquireGPRegister(RegisterType value_type)
{
    auto &available_registers = value_type == RegisterType::Integer ? this->registers.r : this->registers.xmm;

    for (auto &reg : available_registers)
    {
        if (reg.GetRegisterType() != RegisterPurpose::General)
        {
            continue;
        }

        if (reg.GetVolatility() != Volatility::Volatile)
        {
            continue;
        }

        if (!reg.HasValue() || !reg.GetValue()->IsUsed())
        {
            return reg;
        }
    }

    // No free register has been found, so now we dislocate a register with an existing value into the stack.
    this->register_dislocation_count_++;
    for (int i = 0; i < available_registers.size(); i++)
    {
        auto &victim = available_registers[(i + this->register_dislocation_count_) % available_registers.size()];
        if (victim.GetRegisterType() != RegisterPurpose::General || victim.GetVolatility() != Volatility::Volatile)
        {
            continue;
        }

        auto &swap = this->AcquireStackSpace(8);
        this->MoveValue(swap, victim);
        return victim;
    }

    throw std::runtime_error("failed to acquire a new gp register");
}

std::span<Register *> Amd64FunctionTranslator::GetScratchRegisterBank(NativeType type)
{
    if (type == NativeType::Integer)
    {
        return std::span{this->registers.r_volatile};
    }
    else if (type == NativeType::FloatingPoint)
    {
        return std::span{this->registers.xmm_volatile};
    }

    throw std::runtime_error("unknown type");
}

StackAllocationContainer &Amd64FunctionTranslator::AcquireStackSpace(std::size_t size)
{
    for (auto &stack_allocation : this->stack_)
    {
        if (stack_allocation->GetSize() == size && !stack_allocation->HasValue())
        {
            return *stack_allocation;
        }
    }

    auto &stack_allocation = this->stack_.emplace_back(std::make_unique<StackAllocationContainer>(size));
    this->stack_depth_ += static_cast<std::int64_t>(size);
    stack_allocation->SetOffset(this->stack_depth_);

    return *stack_allocation;
}

Amd64Function Amd64FunctionTranslator::Translate()
{
    // Instantiate arguments
    auto const &arg_values = this->ir_function_.GetArgumentValues();
    for (int i = 0; i < arg_values.size(); i++)
    {
        auto value = arg_values[i];
        auto const &value_type = value->GetType();

        if (value_type.GetNativeType() == NativeType::Integer)
        {
            this->registers.r_args[i]->InstantiateValue(value);
        }
        else if (value_type.GetNativeType() == NativeType::FloatingPoint)
        {
            this->registers.xmm_args[i]->InstantiateValue(value);
        }
    }

    // Function Body
    for (auto &block : this->ir_function_.GetBlocks())
    {
        for (auto &instruction : block.GetInstructions())
        {
            instruction->Apply(this);
        }
    }

    /*
     * Entering into a function
     * 1. Push RBP. This will save the old stack from.
     * 2. Save RSP -> RBP. This will initialize the stack frame pointer to use for constant offsets into the stack.
     * 3. Subtract space for stack storage from RSP.
     */
    // Generate Prolog
    if (this->stack_depth_ > 0)
    {
        this->InsertProlog(Amd64Push::M64(this->registers.r[5]));
        this->InsertProlog(Amd64Mov::MR64(this->registers.r[5], this->registers.r[4]));
        this->InsertProlog(Amd64Sub::MI64(this->registers.r[4], this->stack_depth_));
    }

    return std::move(this->function);
}

void Amd64FunctionTranslator::Insert(Amd64Instruction &&inst)
{
    this->function.text_.push_back(std::move(inst));
}

void Amd64FunctionTranslator::InsertProlog(Amd64Instruction &&inst)
{
    this->function.prolog_.push_back(std::move(inst));
}

Amd64FunctionTranslator::Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function) : IRTranslator(ir_function), module(module), function(ir_function) {}
