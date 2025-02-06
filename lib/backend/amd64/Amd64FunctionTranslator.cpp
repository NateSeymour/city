#include <city/JIT.h>
#include <city/backend/amd64/Amd64FunctionTranslator.h>

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
    auto address_reg = this->FindUnusedGPRegister();

    // TODO: PERSIST USED REGISTERS

    Stub stub{
            .label = inst.GetTargetName(),
            .type = StubSourceLocation::Text,
    };
    this->function.text_.push_back(Amd64Mov::OIS(address_reg.GetCode(), std::move(stub)));
    this->function.text_.push_back(Amd64Call::M64(address_reg.GetCode(), Amd64RegisterAccessType::Value));

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

void Amd64FunctionTranslator::Load(Amd64Register &dst, ConstantDataContainer &src) {}

void Amd64FunctionTranslator::Load(Amd64Register &dst, StackAllocationContainer &src) {}

void Amd64FunctionTranslator::Load(Amd64Register &dst, Amd64Register &src)
{
    // Return if attempt to load into the same register.
    if (dst.GetCode() == src.GetCode())
    {
        return;
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
    auto &target_register = reg ? *reg : this->FindUnusedGPRegister(register_type);

    auto container = value->GetContainer();
    container->Load(*this, target_register);
    target_register.AssociateValue(value);

    return &target_register;
}

Amd64Register *Amd64FunctionTranslator::MoveValue(Value &value, Amd64Register &reg, ConflictStrategy strategy)
{
    return this->LoadValue(&value, &reg, strategy);
}

Amd64Register *Amd64FunctionTranslator::InstantiateValue(Value &value, Amd64Register &reg, ConflictStrategy strategy)
{
    if (value.IsInstantiated())
    {
        throw std::runtime_error("cannot reinstantiate value");
    }

    if (reg.HasValue())
    {
        auto conflicting_value = reg.GetValue();

        switch (strategy)
        {
            case ConflictStrategy::Discard:
            {
                conflicting_value->Disassociate();
                reg.Disassociate();
                break;
            }

            case ConflictStrategy::PreferMoveToUnused:
            {
                auto &new_register = this->FindUnusedGPRegister();

                (void)this->MoveValue(*reg.GetValue(), new_register, ConflictStrategy::Push);
                break;
            }

            case ConflictStrategy::Push:
            {
                throw std::runtime_error("unimplemented");
            }
        }
    }

    value.AssociateContainer(&reg);
    reg.AssociateValue(&value);

    return &reg;
}

Amd64Register &Amd64FunctionTranslator::FindUnusedGPRegister(Amd64RegisterValueType value_type)
{
    auto &available_registers = value_type == Amd64RegisterValueType::Integer ? this->registers.r : this->registers.xmm;

    for (auto &reg : available_registers)
    {
        if (reg.GetType() != Amd64RegisterType::GeneralPurpose)
        {
            continue;
        }

        // TODO: save and restore volatile registers instead of just not using them
        if (reg.GetVolatility() != Amd64RegisterVolatility::Volatile)
        {
            continue;
        }

        if (!reg.HasValue() || !reg.GetValue()->IsUsed())
        {
            return reg;
        }
    }

    throw std::runtime_error("register overflow");
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
        this->InsertProlog(Amd64Mov::MR64(this->registers.r[5].GetCode(), this->registers.r[4].GetCode()));
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
