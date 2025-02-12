#ifndef AARCH64FUNCTIONTRANSLATOR_H
#define AARCH64FUNCTIONTRANSLATOR_H

#include "AArch64Function.h"
#include "AArch64Module.h"
#include "city/backend/IRTranslator.h"
#include "city/ir/IRFunction.h"

namespace city
{
    class AArch64FunctionTranslator : IRTranslator
    {
        AArch64Module &module_;
        IRFunction &ir_function_;

    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(DivInst &inst) override;
        void TranslateInstruction(MulInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        void Load(Register &dst, ConstantDataContainer &src) override;
        void Load(Register &dst, StackAllocationContainer &src) override;
        void Load(Register &dst, Register &src) override;

        void Store(StackAllocationContainer &dst, Register &src) override;
        void Store(Register &dst, Register &src) override;

        void Insert(AArch64Instruction &&inst);
        void InsertProlog(AArch64Instruction &&inst);

    public:
        AArch64Function function;

        AArch64FunctionTranslator(AArch64Module &module, IRFunction &ir_function);
    };
} // namespace city

#endif // AARCH64FUNCTIONTRANSLATOR_H
