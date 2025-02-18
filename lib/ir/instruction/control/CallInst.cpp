#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/control/CallInst.h>

using namespace city;

Function *CallInst::GetTarget() const noexcept
{
    return this->target_;
}

std::vector<Value *> const &CallInst::GetArguments() const noexcept
{
    return this->arguments_;
}

void CallInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

CallInst::CallInst(Function *target, std::vector<Value *> arguments) : IRInstruction(target->GetType()), target_(target), arguments_(std::move(arguments))
{
    for (auto argument : arguments)
    {
        argument->IncrementReadCount();
    }
}
