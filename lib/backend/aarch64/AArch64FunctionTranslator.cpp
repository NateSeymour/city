#include "city/backend/aarch64/AArch64FunctionTranslator.h"

using namespace city;

void AArch64FunctionTranslator::TranslateInstruction(AddInst &inst) {}
void AArch64FunctionTranslator::TranslateInstruction(DivInst &inst) {}
void AArch64FunctionTranslator::TranslateInstruction(MulInst &inst) {}
void AArch64FunctionTranslator::TranslateInstruction(SubInst &inst) {}
void AArch64FunctionTranslator::TranslateInstruction(CallInst &inst) {}
void AArch64FunctionTranslator::TranslateInstruction(RetInst &inst) {}

void AArch64FunctionTranslator::Load(Register &dst, ConstantDataContainer &src) {}
void AArch64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src) {}
void AArch64FunctionTranslator::Load(Register &dst, Register &src) {}

void AArch64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src) {}
void AArch64FunctionTranslator::Store(Register &dst, Register &src) {}

void AArch64FunctionTranslator::Insert(AArch64Instruction &&inst)
{
    this->function.text_.push_back(std::move(inst));
}

void AArch64FunctionTranslator::InsertProlog(AArch64Instruction &&inst)
{
    this->function.prolog_.push_back(std::move(inst));
}

AArch64FunctionTranslator::AArch64FunctionTranslator(AArch64Module &module, IRFunction &ir_function) : module_(module), ir_function_(ir_function), function(ir_function) {}
