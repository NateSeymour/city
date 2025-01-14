#include "Amd64Translator.h"

#include "instruction/arithmetic/Amd64Add.h"
#include "instruction/control/Amd64Ret.h"
#include "instruction/memory/Amd64Pop.h"

using namespace city;

Amd64Register *Amd64Translator::GetRegisterByCode(Amd64RegisterCode code)
{
    auto const i = static_cast<std::uint8_t>(code);
    return &this->registers_[i];
}

Amd64Register *Amd64Translator::LoadValue(Value *value, Amd64Register *reg, ConflictStrategy strategy, LoadType load_type) const {}

Amd64Register *Amd64Translator::MoveValue(Value *value, Amd64Register *reg, ConflictStrategy strategy) {}
Amd64Register *Amd64Translator::InstantiateValue(Value *value, Amd64Register *reg, ConflictStrategy strategy) {}

Amd64Register *Amd64Translator::FindUnusedRegister() noexcept
{
    for (auto &reg : this->registers_)
    {
        if (!reg.HasValue() || reg.GetValue()->IsUsed())
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
    (void)this->InstantiateValue(instruction->GetReturnValue(), dsttmp, ConflictStrategy::Discard);

    instruction->GetLHS()->DecrementReadCount();
    instruction->GetRHS()->DecrementReadCount();

    return {};
}

IRTranslationResult Amd64Translator::Translate(RetInst *instruction)
{
    auto return_value = instruction->GetReturnValue();

    if (!return_value->GetType().IsVoid())
    {
        auto rax = this->GetRegisterByCode(Amd64RegisterCode::RAX);
        (void)this->MoveValue(return_value, rax, ConflictStrategy::Discard);
    }

    this->module.Insert(Amd64Pop::O64(Amd64RegisterCode::RBP));
    this->module.Insert(Amd64Ret::ZONear());

    return {};
}
