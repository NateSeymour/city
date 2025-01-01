#include "Amd64Builder.h"

#include "instruction/control/Amd64Ret.h"
#include "instruction/memory/Amd64Mov.h"
#include "instruction/memory/Amd64Pop.h"

using namespace city;

Amd64Register &Amd64Builder::GetRegisterByCode(Amd64RegisterCode code)
{
    auto i = static_cast<uint8_t>(code);
    return this->registers_[i];
}

Amd64Register *Amd64Builder::FindUnusedRegister() const noexcept
{
    for (auto &reg : this->registers_)
    {
    }

    return nullptr;
}

void Amd64Builder::InsertReturnInst(Amd64ReturnType return_type) const
{
    switch (return_type)
    {
        case Amd64ReturnType::Near:
        {
            this->module_.InsertInstruction(Amd64Ret::ZONear());
            break;
        }

        case Amd64ReturnType::Far:
        {
            this->module_.InsertInstruction(Amd64Ret::ZOFar());
            break;
        }
    }
}

void Amd64Builder::InsertPopInst(Amd64RegisterCode reg)
{
    this->module_.InsertInstruction(Amd64Pop::O64(reg));
}

Amd64Register *Amd64Builder::MoveValueToUnusedRegister(Value *value)
{
    for (auto &reg : this->registers_)
    {
        if (!reg.value_ || !reg.value_->IsUsed())
        {
            return this->MoveValueToRegister(value, reg.code_, Amd64RegisterConflictStrategy::Discard);
        }
    }

    // TODO: start popping values out of the registers onto the stack.

    return nullptr;
}

Amd64Register *Amd64Builder::MoveValueToRegister(Value *value, Amd64RegisterCode reg, Amd64RegisterConflictStrategy conflict_strategy)
{
    if (!value)
    {
        return nullptr;
    }

    // WARNING: only discards current value for now.
    auto &physical_reg = this->GetRegisterByCode(reg);

    if (value->IsCompileTimeConstant())
    {
        this->module_.InsertInstruction(Amd64Mov::OIX(reg, value->GetDataBuffer()));
    }
    
    return &physical_reg;
}

Amd64Builder::Amd64Builder(Amd64Module &module) : module_(module) {}
