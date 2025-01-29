#include "CallInst.h"
#include "backend/IRTranslator.h"

using namespace city;

std::string const &CallInst::GetTargetName() const noexcept
{
    return this->target_name_;
}

void CallInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

CallInst::CallInst(Value *return_value, IRFunction *ir_function) : IRInstruction(return_value)
{
    this->target_name_ = ir_function->GetName();
}
