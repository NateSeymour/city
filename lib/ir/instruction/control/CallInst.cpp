#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/control/CallInst.h>

using namespace city;

std::string const &CallInst::GetTargetName() const noexcept
{
    return this->target_name_;
}

void CallInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

CallInst::CallInst(Value *return_value, IRFunction *ir_function) : IRInstruction(return_value)
{
    this->target_name_ = ir_function->GetName();
}
