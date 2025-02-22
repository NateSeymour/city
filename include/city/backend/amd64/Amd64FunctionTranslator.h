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

        [[nodiscard]] std::tuple<RegisterGuard, Amd64Access, std::optional<std::int32_t>> LoadValueRM(Value &value);

        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(DivInst &inst) override;
        void TranslateInstruction(MulInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        template<typename IRInstructionType, typename NativeInstructionType>
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto type = inst.GetType();
            auto optype = type.GetNativeType();
            auto opsize = type.GetSize();

            auto &lhs = *inst.GetLHS();
            auto &rhs = *inst.GetRHS();

            if (optype == NativeType::Integer)
            {
                if constexpr (Amd64EncodingRM<NativeInstructionType>::value)
                {
                    auto dst = this->CopyValueR(lhs);
                    auto [src, access, disp] = this->LoadValueRM(rhs);

                    this->Insert(NativeInstructionType::RM(dst.reg, src.reg, access, disp));

                    dst.reg.InstantiateValue(&inst);
                }
                else if constexpr (Amd64EncodingM<NativeInstructionType>::value)
                {
                }
                else
                {
                    static_assert("impossible to encode operation");
                }
            }
            else if (optype == NativeType::FloatingPoint)
            {
                auto dst = this->CopyValueR(lhs);
                auto [src, access, disp] = this->LoadValueRM(rhs);

                this->Insert(NativeInstructionType::AS(dst.reg, src.reg, opsize, access, disp));

                dst.reg.InstantiateValue(&inst);
            }
        }

        void Load(Register &dst, ConstantDataContainer &src) override;
        void Load(Register &dst, StackAllocationContainer &src) override;
        void Load(Register &dst, StubContainer &src) override;
        void Load(Register &dst, Register &src) override;

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
