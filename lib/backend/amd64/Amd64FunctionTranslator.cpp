#include <city/JIT.h>
#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/container/StackAllocationContainer.h>

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
    auto address_reg = this->AcquireGPRegister();

    // TODO: PERSIST USED REGISTERS

    Stub stub{
            .label = inst.GetTargetName(),
            .type = StubSourceLocation::Text,
    };
    this->function.text_.push_back(Amd64Mov::OIS(address_reg, std::move(stub)));
    this->function.text_.push_back(Amd64Call::M64(address_reg.GetCode(), Amd64Mod::Value));

    (void)this->InstantiateValue(*inst.GetReturnValue(), this->registers.r[0], ConflictStrategy::Discard);
}

void Amd64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto return_value = inst.GetReturnValue();
    if (return_value->IsInstantiated())
    {
        if (return_value->GetType().GetNativeType() == NativeType::Integer)
        {
            (void)this->MoveValue(*return_value, this->registers.r[0], ConflictStrategy::Discard);
        }
        else
        {
            (void)this->MoveValue(*return_value, this->registers.xmm[0], ConflictStrategy::Discard);
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
    // TODO: FIX!!!
    Stub stub{
            .src_offset = src.GetOffset(),
            .type = StubSourceLocation::Data,
    };

    this->Insert(Amd64Mov::OIS(target.GetCode(), std::move(stub)));

    auto value_type = container.GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->translator.Insert(Amd64Mov::RMX(target.GetCode(), target.GetCode(), container.GetSize(), Amd64Mod::Pointer));
    }
    else
    {
        this->translator.Insert(Amd64Mov::SDA(target.GetCode(), target.GetCode(), Amd64Mod::Pointer));
    }
}

void Amd64FunctionTranslator::Load(Amd64Register &dst, StackAllocationContainer &src)
{
    auto &rbp = this->registers.r[5];

    if (dst.GetValueType() == Amd64RegisterValueType::Integer)
    {
        this->Insert(Amd64Mov::RMX(dst, rbp, src.GetSize(), Amd64Mod::Pointer, src.GetOffset() * -1));
    }
    else if (dst.GetValueType() == Amd64RegisterValueType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, rbp, Amd64Mod::Pointer, src.GetOffset() * -1));
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

void Amd64FunctionTranslator::Store(StackAllocationContainer &dst, Amd64Register &src) {}

Amd64Register *Amd64FunctionTranslator::LoadValue(Value *value, Amd64Register *reg, ConflictStrategy strategy, LoadType load_type)
{
    if (!value->IsInstantiated())
    {
        throw std::runtime_error("impossible to load uninstantiated value");
    }

    auto value_type = value->GetType();
    auto register_type = value_type.GetNativeType() == NativeType::Integer ? Amd64RegisterValueType::Integer : Amd64RegisterValueType::FloatingPoint;
    auto &target_register = reg ? *reg : this->AcquireGPRegister(register_type);

    auto container = value->GetContainer();
    container->Load(*this, target_register);
    target_register.AssociateValue(value);

    return &target_register;
}

void Amd64FunctionTranslator::MoveValue(Value &value, Container &dst, ConflictStrategy strategy)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("impossible to move uninstantiated value");
    }

    if (dst.HasValue() && dst.GetValue()->IsUsed())
    {
        switch (strategy)
        {
            case ConflictStrategy::Discard:
            {
                dst.GetValue()->Disassociate();
                dst.Disassociate();
                break;
            }

            case ConflictStrategy::Save:
            {
                auto size = dst.GetValue()->GetType().GetSize();
                auto &stack_container = this->AcquireStackSpace(size);
                this->MoveValue(*dst.GetValue(), stack_container, ConflictStrategy::Discard);
                break;
            }
        }
    }
}

void Amd64FunctionTranslator::InstantiateValue(Value &value, Amd64Register &reg)
{
    if (value.IsInstantiated())
    {
        throw std::runtime_error("cannot reinstantiate value");
    }

    if (reg.HasValue() && reg.GetValue()->IsUsed())
    {
        auto &old_value = *reg.GetValue();

        auto size = reg.GetValue()->GetType().GetSize();
        auto &stack_container = this->AcquireStackSpace(size);

        old_value.AssociateContainer(&stack_container);
        stack_container.AssociateValue(&old_value);
        
        this->Store(stack_container, reg);
    }

    value.AssociateContainer(&reg);
    reg.AssociateValue(&value);
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

        auto &stack_container = this->AcquireStackSpace(8);
        this->MoveValue(*victim.GetValue(), stack_container, ConflictStrategy::Discard);
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

    auto &stack_allcoation = this->local_swap_.emplace_back(std::make_unique<StackAllocationContainer>(size));
    stack_allcoation->SetOffset(this->stack_depth);
    this->stack_depth += size;

    return *stack_allcoation;
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
        this->InsertProlog(Amd64Push::O64(this->registers.r[5].GetCode()));
        this->InsertProlog(Amd64Mov::MR64(this->registers.r[5], this->registers.r[4]));
        this->InsertProlog(Amd64Sub::MI64(this->registers.r[4].GetCode(), this->stack_depth));
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

Amd64FunctionTranslator::Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function) : module(module), ir_function(ir_function), function({ir_function.GetName()}) {}
