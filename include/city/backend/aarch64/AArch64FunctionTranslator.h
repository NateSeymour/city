#ifndef AARCH64FUNCTIONTRANSLATOR_H
#define AARCH64FUNCTIONTRANSLATOR_H

#include "AArch64Function.h"
#include "AArch64RegisterBank.h"
#include "city/backend/IRTranslator.h"
#include "city/ir/IRFunction.h"

namespace city
{
    class AArch64FunctionTranslator : public IRTranslator
    {
        AArch64RegisterBank reg_;
        Value frame_{{16, NativeType::Integer}};

    protected:
        [[nodiscard]] std::span<Register *> GetScratchRegisterBank(NativeType type) override;

        template<typename IRInstructionType, typename NativeInstructionType>
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto type = inst.GetType();
            auto optype = type.GetNativeType();
            auto opsize = type.GetSize();

            auto &lhs = *inst.GetLHS();
            auto &rhs = *inst.GetRHS();

            Register *dst = nullptr;
            auto src1 = this->LoadValueR(lhs);
            auto src2 = this->LoadValueR(rhs);

            if (src1.reg.GetValue()->GetReadCount() <= 1)
            {
                dst = &src1.reg;
            }
            else if (src2.reg.GetValue()->GetReadCount() <= 1)
            {
                dst = &src2.reg;
            }
            else
            {
                auto dstguard = this->AcquireScratchRegister(optype);
                dst = &dstguard.reg;
            }

            if (optype == NativeType::Integer)
            {
                this->Insert(NativeInstructionType::R(*dst, src1.reg, src2.reg, opsize));
            }
            else if (optype == NativeType::FloatingPoint)
            {
                this->Insert(NativeInstructionType::F(*dst, src1.reg, src2.reg, opsize));
            }

            dst->InstantiateValue(&inst);
        }

        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(DivInst &inst) override;
        void TranslateInstruction(MulInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        void Load(Register &dst, ConstantDataContainer &src) override;
        void Load(Register &dst, StackAllocationContainer &src) override;
        void Load(Register &dst, StubContainer &src) override;
        void Load(Register &dst, Register &src) override;

        void Store(StackAllocationContainer &dst, Register &src) override;
        void Store(Register &dst, Register &src) override;

        void Insert(AArch64Instruction &&inst);
        void InsertProlog(AArch64Instruction &&inst);

    public:
        AArch64Function function;

        AArch64FunctionTranslator(NativeModule &module, IRFunction &ir_function);
    };
} // namespace city

#endif // AARCH64FUNCTIONTRANSLATOR_H
