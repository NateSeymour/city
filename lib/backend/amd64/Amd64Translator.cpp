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

IRTranslationResult Amd64FunctionTranslator::Translate(AddInst *instruction)
{
    auto dsttmp = this->LoadValue(instruction->GetLHS());
    auto srctmp = this->LoadValue(instruction->GetRHS());

    this->module.Insert(Amd64Add::MR64(dsttmp->GetCode(), srctmp->GetCode()));
    (void)this->InstantiateValue(*instruction->GetReturnValue(), *dsttmp, ConflictStrategy::Discard);

    srctmp->Disassociate();

    instruction->GetLHS()->DecrementReadCount();
    instruction->GetRHS()->DecrementReadCount();

    return {};
}

IRTranslationResult Amd64FunctionTranslator::Translate(FAddInst *instruction)
{
    auto dsttmp = this->LoadValue(instruction->GetLHS());
    auto srctmp = this->LoadValue(instruction->GetRHS());

    this->module.Insert(Amd64Add::SDA(dsttmp->GetCode(), srctmp->GetCode()));
    (void)this->InstantiateValue(*instruction->GetReturnValue(), *dsttmp, ConflictStrategy::Discard);

    srctmp->Disassociate();

    instruction->GetLHS()->DecrementReadCount();
    instruction->GetRHS()->DecrementReadCount();

    return {};
}

IRTranslationResult Amd64FunctionTranslator::Translate(SubInst *instruction)
{
    auto dsttmp = this->LoadValue(instruction->GetLHS());
    auto srctmp = this->LoadValue(instruction->GetRHS());

    this->module.Insert(Amd64Sub::MR64(dsttmp->GetCode(), srctmp->GetCode()));
    (void)this->InstantiateValue(*instruction->GetReturnValue(), *dsttmp, ConflictStrategy::Discard);

    srctmp->Disassociate();

    instruction->GetLHS()->DecrementReadCount();
    instruction->GetRHS()->DecrementReadCount();

    return {};
}

IRTranslationResult Amd64FunctionTranslator::Translate(CallInst *instruction)
{
    auto address_reg = this->FindUnusedRegister();

    Stub stub{
            .label = instruction->GetTargetName(),
            .type = StubSourceLocation::Text,
    };
    this->module.Insert(Amd64Mov::OIS(address_reg->GetCode(), std::move(stub)));

    this->module.Insert(Amd64Call::M64(address_reg->GetCode(), Amd64RegisterAccessType::Value));

    auto return_value = instruction->GetReturnValue();
    auto rax = this->GetRegisterByCode(Amd64RegisterCode::RAX);
    (void)this->InstantiateValue(*return_value, *rax, ConflictStrategy::Discard);

    return {};
}

IRTranslationResult Amd64FunctionTranslator::Translate(RetInst *instruction)
{
    auto return_value = instruction->GetReturnValue();
    auto &return_register = [&]() -> Amd64Register &
    {
        if (return_value->GetType().GetNativeType() == NativeType::Integer)
        {
            return this->registers.r[0];
        }
        else
        {
            return this->registers.xmm[0];
        }
    }();

    if (!return_value->GetType().IsVoid() || return_value->IsInstantiated())
    {
        (void)this->MoveValue(*return_value, return_register, ConflictStrategy::Discard);
    }
    else
    {
        // In the case of a void return value, simply return zero.
        this->module.Insert(Amd64Mov::OI32(return_register.GetCode(), 0));
    }

    this->module.Insert(Amd64Leave::ZO());
    this->module.Insert(Amd64Ret::ZONear());

    return {};
}
