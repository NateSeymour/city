#include <city/JIT.h>
#include <city/backend/amd64/Amd64FunctionTranslator.h>

#include <city/backend/amd64/instruction/arithmetic/Amd64Add.h>
#include <city/backend/amd64/instruction/arithmetic/Amd64Sub.h>
#include <city/backend/amd64/instruction/control/Amd64Call.h>
#include <city/backend/amd64/instruction/control/Amd64Leave.h>
#include <city/backend/amd64/instruction/control/Amd64Ret.h>
#include <city/backend/amd64/instruction/memory/Amd64Mov.h>
#include <city/backend/amd64/instruction/memory/Amd64Pop.h>

using namespace city;

void Amd64FunctionTranslator::TranslateInstruction(AddInst &inst)
{
    this->TranslateBinaryInstruction<AddInst, Amd64Add>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(FAddInst &inst)
{
    this->TranslateBinaryInstruction<FAddInst, Amd64Add>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(SubInst &inst)
{
    this->TranslateBinaryInstruction<SubInst, Amd64Add>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(CallInst &inst)
{
    auto address_reg = this->FindUnusedRegister();

    // TODO: PERSIST USED REGISTERS

    Stub stub{
            .label = inst.GetTargetName(),
            .type = StubSourceLocation::Text,
    };
    this->function.text_.push_back(Amd64Mov::OIS(address_reg->GetCode(), std::move(stub)));
    this->function.text_.push_back(Amd64Call::M64(address_reg->GetCode(), Amd64RegisterAccessType::Value));

    (void)this->InstantiateValue(*inst.GetReturnValue(), this->registers.r[0], ConflictStrategy::Discard);
}

void Amd64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto return_value = inst.GetReturnValue();
    if (!return_value->GetType().IsVoid() || return_value->IsInstantiated())
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
    else
    {
        this->function.text_.push_back(Amd64Mov::OI64(this->registers.r[0].GetCode(), 0));
    }

    this->function.text_.push_back(Amd64Leave::ZO());
    this->function.text_.push_back(Amd64Ret::ZONear());
}

Amd64Register *Amd64FunctionTranslator::LoadValue(Value *value, Amd64Register *reg, ConflictStrategy strategy, LoadType load_type)
{
    if (!value->IsInstantiated())
    {
        throw std::runtime_error("impossible to load uninstantiated value");
    }

    if (!reg)
    {
        reg = this->FindUnusedRegister();
    }

    auto container = value->GetContainer();
    container->LoadIntoAmd64Register(&this->register_loader, *reg);
    reg->AssociateValue(value);

    return reg;
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
        switch (strategy)
        {
            case ConflictStrategy::Discard:
            {
                reg.Disassociate();
                break;
            }

            case ConflictStrategy::PreferMoveToUnused:
            {
                auto new_register = this->FindUnusedRegister();

                if (new_register)
                {
                    (void)this->MoveValue(*reg.GetValue(), *new_register, ConflictStrategy::Push);
                    break;
                }

                // INTENTIONALLY fall through to PUSH, because unused was unsuccessful
            }

            case ConflictStrategy::Push:
            {
                // DO SOMETHING
                break;
            }
        }
    }

    value.AssociateContainer(&reg);
    reg.AssociateValue(&value);

    return &reg;
}

Amd64Register *Amd64FunctionTranslator::FindUnusedRegister() noexcept
{
    for (auto &reg : this->registers_)
    {
        if (!reg.HasValue() || !reg.GetValue()->IsUsed())
        {
            return &reg;
        }
    }

    return nullptr;
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

    // Function Prolog

    return std::move(this->function);
}

void Amd64FunctionTranslator::Insert(Amd64Instruction &&inst)
{
    this->function.text_.push_back(std::move(inst));
}

Amd64FunctionTranslator::Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function) : module(module), ir_function(ir_function), function({ir_function.GetName()}) {}
