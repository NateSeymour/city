#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <city/backend/IRTranslator.h>
#include <city/container/StackAllocationContainer.h>
#include "Amd64Function.h"
#include "Amd64RegisterBank.h"

namespace city
{
    class Amd64FunctionTranslator : IRTranslator
    {
        Amd64RegisterBank reg_;

    protected:
        [[nodiscard]] std::span<Register *> GetScratchRegisterBank(NativeType type) override;

        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(DivInst &inst) override;
        void TranslateInstruction(MulInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        template<typename IRInstructionType, typename NativeInstructionType>
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto op = this->PrepareBinaryOperation(inst, true);

            if (op.optype == NativeType::Integer)
            {
                if constexpr (CInstRM<NativeInstructionType>::value)
                {
                    this->Insert(NativeInstructionType::RMX(op.src1, op.src2, op.opsize));
                }
                else if constexpr (CInstM<NativeInstructionType>::value)
                {
                }
                else
                {
                    static_assert("impossible to encode operation");
                }
            }
            else if (op.optype == NativeType::FloatingPoint)
            {
                this->Insert(NativeInstructionType::SDA(op.src1, op.src2));
            }

            op.Persist();
        }

        void Load(Register &dst, ConstantDataContainer &src) override;
        void Load(Register &dst, StackAllocationContainer &src) override;
        void Load(Register &dst, StubContainer &src) override;
        void Load(Register &dst, Register &src) override;

    protected:
        void Store(StackAllocationContainer &dst, Register &src) override;
        void Store(Register &dst, Register &src) override;

        void Insert(Amd64Instruction &&inst);
        void InsertProlog(Amd64Instruction &&inst);

    public:
        Amd64Function function;

        explicit Amd64FunctionTranslator(NativeModule &module, IRFunction &ir_function);
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
