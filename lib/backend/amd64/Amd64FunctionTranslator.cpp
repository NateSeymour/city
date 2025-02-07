#include <city/JIT.h>
#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/container/StackAllocationContainer.h>
#include <stack>

#include <city/backend/amd64/instruction/arithmetic/Amd64Add.h>
#include <city/backend/amd64/instruction/arithmetic/Amd64Sub.h>
#include <city/backend/amd64/instruction/control/Amd64Call.h>
#include <city/backend/amd64/instruction/control/Amd64Leave.h>
#include <city/backend/amd64/instruction/control/Amd64Ret.h>
#include <city/backend/amd64/instruction/memory/Amd64Mov.h>
#include <city/backend/amd64/instruction/memory/Amd64Push.h>

using namespace city;

void Amd64FunctionTranslator::TranslateInstruction(AddInst &inst)
{
    this->TranslateBinaryInstruction<AddInst, Amd64Add>(inst);
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
            .label = inst.GetTargetName(),
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

    this->Insert(Amd64Call::M64(address_reg));

    auto native_type = inst.GetReturnValue()->GetType().GetNativeType();
    if (native_type == NativeType::Integer)
    {
        this->Associate(*inst.GetReturnValue(), this->registers.r[0]);
    }
    else if (native_type == NativeType::FloatingPoint)
    {
        this->Associate(*inst.GetReturnValue(), this->registers.xmm[0]);
    }
}

void Amd64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto return_value = inst.GetReturnValue();
    if (return_value->IsInstantiated())
    {
        auto native_type = return_value->GetType().GetNativeType();
        if (native_type == NativeType::Integer)
        {
            this->MoveValue(this->registers.r[0], *return_value, ConflictStrategy::Discard);
        }
        else if (native_type == NativeType::FloatingPoint)
        {
            this->MoveValue(this->registers.xmm[0], *return_value, ConflictStrategy::Discard);
        }
    }

    if (this->stack_depth > 0)
    {
        this->Insert(Amd64Leave::ZO());
    }

    this->function.text_.push_back(Amd64Ret::ZONear());
}

void Amd64FunctionTranslator::Load(Amd64Register &dst, ConstantDataContainer &src)
{
    Stub stub{
            .src_offset = src.GetOffset(),
            .type = StubSourceLocation::Data,
    };

    auto value_type = src.GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->Insert(Amd64Mov::OIS(dst, std::move(stub)));
        this->Insert(Amd64Mov::RMX(dst, dst, dst.GetSize(), Amd64Mod::Pointer));
    }
    else
    {
        auto &stubtmp = this->AcquireGPRegister(Amd64RegisterValueType::Integer);
        this->Insert(Amd64Mov::OIS(stubtmp, std::move(stub)));
        this->Insert(Amd64Mov::SDA(dst, stubtmp, Amd64Mod::Pointer));
    }
}

void Amd64FunctionTranslator::Load(Amd64Register &dst, StackAllocationContainer &src)
{
    auto &rbp = this->registers.r[5];

    if (dst.GetValueType() == Amd64RegisterValueType::Integer)
    {
        this->Insert(Amd64Mov::RMX(dst, rbp, src.GetSize(), Amd64Mod::DisplacedPointer, src.GetOffset() * -1));
    }
    else if (dst.GetValueType() == Amd64RegisterValueType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, rbp, Amd64Mod::DisplacedPointer, src.GetOffset() * -1));
    }
}

void Amd64FunctionTranslator::Load(Amd64Register &dst, Amd64Register &src)
{
    // Return if attempt to load into the same register.
    if (dst.GetCode() == src.GetCode())
    {
        return;
    }

    if (dst.GetValueType() == Amd64RegisterValueType::Integer)
    {
        this->Insert(Amd64Mov::RM64(dst, src));
    }
    else if (dst.GetValueType() == Amd64RegisterValueType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, src));
    }
}

void Amd64FunctionTranslator::Store(StackAllocationContainer &dst, Amd64Register &src)
{
    auto &rbp = this->registers.r[5];

    if (src.GetValueType() == Amd64RegisterValueType::Integer)
    {
        this->Insert(Amd64Mov::MR64(rbp, src, Amd64Mod::DisplacedPointer, dst.GetOffset() * -1));
    }
    else if (src.GetValueType() == Amd64RegisterValueType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(rbp, src, Amd64Mod::DisplacedPointer, dst.GetOffset() * -1));
    }
}

void Amd64FunctionTranslator::Store(Amd64Register &dst, Amd64Register &src)
{
    this->Load(dst, src);
}

Amd64Register &Amd64FunctionTranslator::CopyValue(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("impossible to copy uninstantiated value");
    }

    auto value_type = value.GetType();
    auto register_type = value_type.GetNativeType() == NativeType::Integer ? Amd64RegisterValueType::Integer : Amd64RegisterValueType::FloatingPoint;
    auto &target_register = this->AcquireGPRegister(register_type);

    auto src = value.GetContainer();
    src->Load(*this, target_register);
    target_register.AssociateValue(&value);

    return target_register;
}

void Amd64FunctionTranslator::MoveValue(StackAllocationContainer &dst, Amd64Register &src)
{
    if (!src.HasValue())
    {
        throw std::runtime_error("source has no value to move");
    }

    if (dst.HasValue() && dst.GetValue()->IsUsed())
    {
        throw std::runtime_error("unresolvable value conflict");
    }

    auto &value = *src.GetValue();
    this->Store(dst, src);

    src.Disassociate();
    value.Disassociate();
    this->Associate(value, dst);
}

void Amd64FunctionTranslator::MoveValue(Amd64Register &dst, Amd64Register &src, ConflictStrategy strategy)
{
    if (!src.HasValue())
    {
        throw std::runtime_error("source has no value to move");
    }

    this->HandleConflict(dst, strategy);

    auto &value = *src.GetValue();
    this->Store(dst, src);

    src.Disassociate();
    value.Disassociate();
    this->Associate(value, dst);
}

void Amd64FunctionTranslator::MoveValue(Amd64Register &dst, Value &value, ConflictStrategy strategy)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot move uninstantiated value");
    }

    this->HandleConflict(dst, strategy);

    auto &src = *value.GetContainer();
    src.Load(*this, dst);

    src.Disassociate();
    value.Disassociate();
    this->Associate(value, dst);
}

void Amd64FunctionTranslator::HandleConflict(Amd64Register &reg, ConflictStrategy strategy)
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

Amd64Register &Amd64FunctionTranslator::AcquireGPRegister(Amd64RegisterValueType value_type)
{
    auto &available_registers = value_type == Amd64RegisterValueType::Integer ? this->registers.r : this->registers.xmm;

    for (auto &reg : available_registers)
    {
        if (reg.GetType() != Amd64RegisterType::GeneralPurpose)
        {
            continue;
        }

        if (reg.GetVolatility() != Amd64RegisterVolatility::Volatile)
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
        if (victim.GetType() != Amd64RegisterType::GeneralPurpose || victim.GetVolatility() != Amd64RegisterVolatility::Volatile)
        {
            continue;
        }

        auto &swap = this->AcquireStackSpace(8);
        this->MoveValue(swap, victim);
        return victim;
    }

    throw std::runtime_error("failed to acquire a new gp register");
}

StackAllocationContainer &Amd64FunctionTranslator::AcquireStackSpace(std::size_t size)
{
    for (auto &stack_allocation : this->local_swap_)
    {
        if (stack_allocation->GetSize() == size && !stack_allocation->HasValue())
        {
            return *stack_allocation;
        }
    }

    auto &stack_allocation = this->local_swap_.emplace_back(std::make_unique<StackAllocationContainer>(size));
    stack_allocation->SetOffset(this->stack_depth);
    this->stack_depth += static_cast<std::int64_t>(size);

    return *stack_allocation;
}

Amd64Function Amd64FunctionTranslator::Translate()
{
    // Function Body
    for (auto &block : this->ir_function.blocks_)
    {
        for (auto &instruction : block.instructions_)
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
    if (this->stack_depth > 0)
    {
        this->InsertProlog(Amd64Push::O64(this->registers.r[5]));
        this->InsertProlog(Amd64Mov::MR64(this->registers.r[5], this->registers.r[4]));
        this->InsertProlog(Amd64Sub::MI64(this->registers.r[4], this->stack_depth));
    }

    return std::move(this->function);
}

void Amd64FunctionTranslator::Associate(Value &value, Container &container)
{
    if (value.IsInstantiated())
    {
        throw std::runtime_error("value is already associated to container");
    }

    if (container.HasValue() && container.GetValue()->IsUsed())
    {
        throw std::runtime_error("cannot associate one value on top of another");
    }

    value.AssociateContainer(&container);
    container.AssociateValue(&value);
}

void Amd64FunctionTranslator::Insert(Amd64Instruction &&inst)
{
    this->function.text_.push_back(std::move(inst));
}

void Amd64FunctionTranslator::InsertProlog(Amd64Instruction &&inst)
{
    this->function.prolog_.push_back(std::move(inst));
}

Amd64FunctionTranslator::Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function) : module(module), ir_function(ir_function), function({ir_function.GetName()}) {}
