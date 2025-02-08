#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/control/CallInst.h>

using namespace city;

std::string const &CallInst::GetTargetName() const noexcept
{
    return this->target_name_;
}

std::vector<Value *> const &CallInst::GetArgs() const noexcept
{
    return this->args_;
}

void CallInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

CallInst::CallInst(Value *return_value, Function *ir_function, std::vector<Value *> const &args) : IRInstruction(return_value), args_(args)
{
    this->target_name_ = ir_function->GetName();
}
