#ifndef AARCH64FUNCTIONTRANSLATOR_H
#define AARCH64FUNCTIONTRANSLATOR_H

#include "AArch64Function.h"
#include "AArch64RegisterBank.h"
#include "city/backend/IRTranslator.h"
#include "city/ir/IRFunction.h"

namespace city
{
    struct AArch64BinaryOperation
    {
        IRBinaryInstruction &inst;
        Register &dst;
        Register &src1;
        Register &src2;
        std::size_t opsize;
        NativeType optype;

        void Persist() const
        {
            this->inst.GetLHS()->DecrementReadCount();
            this->inst.GetRHS()->DecrementReadCount();

            dst.InstantiateValue(&inst);

            dst.ClearTempValue();
            src1.ClearTempValue();
            src2.ClearTempValue();
        }
    };

    class AArch64FunctionTranslator : IRTranslator
    {
        AArch64Module &module_;
        AArch64RegisterBank reg_;

    protected:
        [[nodiscard]] std::span<Register *> GetScratchRegisterBank(NativeType type) override;

        [[nodiscard]] AArch64BinaryOperation PrepareBinaryOperation(IRBinaryInstruction &inst);

        template<typename IRInstructionType, typename NativeInstructionType>
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto op = this->PrepareBinaryOperation(inst);

            if (op.optype == NativeType::Integer)
            {
                this->Insert(NativeInstructionType::R(op.dst, op.src1, op.src2, op.opsize));
            }
            else if (op.optype == NativeType::FloatingPoint)
            {
                this->Insert(NativeInstructionType::F(op.dst, op.src1, op.src2, op.opsize));
            }

            op.Persist();
        }

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
