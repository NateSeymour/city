#include "Amd64Builder.h"

#include "instruction/control/Amd64Ret.h"
#include "instruction/memory/Amd64Pop.h"

using namespace city;

Amd64Register *Amd64Builder::FindUnusedRegister() const noexcept
{
    for (auto &reg : this->registers_)
    {
    }
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

Amd64Register *Amd64Builder::MoveValueToUnusedRegister(Value *value) {}
Amd64Register *Amd64Builder::MoveValueToRegister(Value *value, Amd64RegisterCode reg, Amd64RegisterConflictStrategy conflict_strategy) {}
Amd64Builder::Amd64Builder(Amd64Module &module) : module_(module) {}
