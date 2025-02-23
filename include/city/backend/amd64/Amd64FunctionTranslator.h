#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <city/backend/IRTranslator.h>
#include <city/container/StackAllocationContainer.h>
#include "Amd64Function.h"
#include "Amd64RegisterBank.h"
#include "instruction/arithmetic/Amd64Cqo.h"
#include "instruction/arithmetic/Amd64Xor.h"

#include <tuple>

namespace city
{
    class Amd64FunctionTranslator : IRTranslator
    {
        Amd64RegisterBank reg_;

    protected:
        [[nodiscard]] std::span<Register *> GetScratchRegisterBank(NativeType type) override;

        [[nodiscard]] std::tuple<Register &, Amd64Access, std::optional<std::int32_t>> LoadValueRM(Value &value);

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
                    RegisterGuard dst = this->CopyValueR(lhs); // Lock dst as to no reuse it for src.
                    auto [src, access, disp] = this->LoadValueRM(rhs);

                    this->Insert(NativeInstructionType::RM(dst.reg, src, access, disp));

                    dst.reg.InstantiateValue(&inst);
                }
                else if constexpr (Amd64EncodingM<NativeInstructionType>::value)
                {
                    // Acquire RDX:RAX
                    RegisterGuard rax = this->AcquireScratchRegister(this->reg_.r[0]);
                    RegisterGuard rdx = this->AcquireScratchRegister(this->reg_.r[2]);

                    // Load Arguments
                    (void)this->LoadValueR(rax.reg, lhs);

                    // Sign/zero extend based on type.
                    if (type.IsSigned())
                    {
                        this->Insert(Amd64Cqo::ZO());
                    }
                    else
                    {
                        this->Insert(Amd64Xor::RM(rdx.reg, rdx.reg));
                    }

                    auto [src, access, disp] = this->LoadValueRM(rhs);

                    this->Insert(NativeInstructionType::M(src, type.IsSigned(), access, disp));

                    rax.reg.InstantiateValue(&inst);
                }
                else
                {
                    static_assert("impossible to encode operation");
                }
            }
            else if (optype == NativeType::FloatingPoint)
            {
                RegisterGuard dst = this->CopyValueR(lhs);
                auto [src, access, disp] = this->LoadValueRM(rhs);

                this->Insert(NativeInstructionType::AS(dst.reg, src, opsize, access, disp));

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
