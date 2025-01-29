#include "Amd64Translator.h"
#include "JIT.h"

#include "instruction/arithmetic/Amd64Add.h"
#include "instruction/arithmetic/Amd64Sub.h"
#include "instruction/control/Amd64Call.h"
#include "instruction/control/Amd64Ret.h"
#include "instruction/memory/Amd64Mov.h"
#include "instruction/memory/Amd64Pop.h"

using namespace city;

Amd64Register *Amd64Translator::GetRegisterByCode(Amd64RegisterCode code)
{
    auto const i = static_cast<std::uint8_t>(code);
    return &this->registers_[i];
}

Amd64Register *Amd64Translator::LoadValue(Value *value, Amd64Register *reg, ConflictStrategy strategy, LoadType load_type)
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

Amd64Register *Amd64Translator::MoveValue(Value &value, Amd64Register &reg, ConflictStrategy strategy)
{
    return this->LoadValue(&value, &reg, strategy);
}

Amd64Register *Amd64Translator::InstantiateValue(Value &value, Amd64Register &reg, ConflictStrategy strategy)
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

Amd64Register *Amd64Translator::FindUnusedRegister() noexcept
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

IRTranslationResult Amd64Translator::Translate(AddInst *instruction)
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

IRTranslationResult Amd64Translator::Translate(SubInst *instruction)
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

IRTranslationResult Amd64Translator::Translate(CallInst *instruction)
{
    auto address_reg = this->FindUnusedRegister();

    auto movinst = Amd64Mov::OI64(address_reg->GetCode(), city::kLinkerCanary);
    movinst.SetLinkerRef(instruction->GetTargetName());
    this->module.Insert(std::move(movinst));

    this->module.Insert(Amd64Call::M64(address_reg->GetCode(), Amd64Mod::Register));

    auto return_value = instruction->GetReturnValue();
    auto rax = this->GetRegisterByCode(Amd64RegisterCode::RAX);
    (void)this->InstantiateValue(*return_value, *rax, ConflictStrategy::Discard);

    return {};
}

IRTranslationResult Amd64Translator::Translate(RetInst *instruction)
{
    auto return_value = instruction->GetReturnValue();
    auto rax = this->GetRegisterByCode(Amd64RegisterCode::RAX);

    if (!return_value->GetType().IsVoid() || return_value->IsInstantiated())
    {
        (void)this->MoveValue(*return_value, *rax, ConflictStrategy::Discard);
    }
    else
    {
        // In the case of a void return value, simply return zero.
        this->module.Insert(Amd64Mov::OI32(Amd64RegisterCode::RAX, 0));
    }

    this->module.Insert(Amd64Pop::O64(Amd64RegisterCode::RBP));
    this->module.Insert(Amd64Ret::ZONear());

    return {};
}
