#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <city/backend/IRTranslator.h>
#include <city/container/StackAllocationContainer.h>
#include "Amd64Function.h"
#include "Amd64Module.h"
#include "container/Amd64RegisterBank.h"

namespace city
{
    enum class ConflictStrategy
    {
        Save,
        Discard,
    };

    enum class LoadType
    {
        Value,
        Pointer,
        Optimal,
    };

    template<typename IRInstructionType, typename NativeInstructionType>
    concept Amd64TranslationPair = requires {
        std::is_base_of_v<IRInstructionType, IRInstruction>;
        std::is_base_of_v<NativeInstructionType, Amd64Instruction>;
    };

    class Amd64FunctionTranslator : IRTranslator
    {
        friend class ConstantDataContainer;
        friend class StackAllocationContainer;
        friend class Amd64Register;

        std::uint64_t register_dislocation_count_ = 0;

    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(DivInst &inst) override;
        void TranslateInstruction(MulInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        [[nodiscard]] Amd64Register &PrepareDestinationValue(Value &value);
        [[nodiscard]] std::tuple<Amd64Register &, Amd64Mod, std::int32_t> PrepareSourceValue(Value &value);

        template<typename IRInstructionType, typename NativeInstructionType>
            requires CInstSDA<NativeInstructionType>
        void TranslateFPBinaryInstruction(IRInstructionType &inst)
        {
            auto lhs = *inst.GetLHS();
            auto rhs = *inst.GetRHS();

            Amd64Register &dsttmp = this->PrepareDestinationValue(lhs);
            auto [srctmp, mod, disp] = this->PrepareSourceValue(rhs);

            this->Insert(NativeInstructionType::SDA(dsttmp, srctmp, mod, disp));

            lhs.DecrementReadCount();
            rhs.DecrementReadCount();

            this->Associate(inst, dsttmp);
        }

        template<typename IRInstructionType, typename NativeInstructionType>
        void TranslateIntegerBinaryInstruction(IRInstructionType &inst)
        {
            auto const &type = inst.GetType();

            auto lhs = *inst.GetLHS();
            auto rhs = *inst.GetRHS();

            if constexpr (CInstRM<NativeInstructionType>::value)
            {
                Amd64Register &dsttmp = this->PrepareDestinationValue(lhs);
                auto [srctmp, mod, disp] = this->PrepareSourceValue(rhs);

                this->Insert(NativeInstructionType::RMX(dsttmp, srctmp, type.GetSize(), mod, disp));

                lhs.DecrementReadCount();
                rhs.DecrementReadCount();

                this->Associate(inst, dsttmp);
            }
            else if constexpr (CInstM<NativeInstructionType>::value)
            {
            }
            else
            {
                static_assert("impossible to encode operation");
            }
        }

        template<typename IRInstructionType, typename NativeInstructionType>
            requires Amd64TranslationPair<IRInstructionType, NativeInstructionType>
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto const &type = inst.GetType();
            if (type.GetSize() > 8)
            {
                throw std::runtime_error("operand is too big");
            }

            switch (type.GetNativeType())
            {
                case NativeType::Integer:
                {
                    this->TranslateIntegerBinaryInstruction<IRInstructionType, NativeInstructionType>(inst);
                    break;
                }

                case NativeType::FloatingPoint:
                {
                    this->TranslateFPBinaryInstruction<IRInstructionType, NativeInstructionType>(inst);
                    break;
                }

                case NativeType::Void:
                {
                    throw std::runtime_error("unable to perform binary operation on void");
                }
            }
        }

        void Load(Amd64Register &dst, ConstantDataContainer &src);
        void Load(Amd64Register &dst, StackAllocationContainer &src);
        void Load(Amd64Register &dst, Amd64Register &src);

        void Store(StackAllocationContainer &dst, Amd64Register &src);
        void Store(Amd64Register &dst, Amd64Register &src);

        [[nodiscard]] Amd64Register &CopyValue(Value &value);

        void MoveValue(StackAllocationContainer &dst, Amd64Register &src);
        void MoveValue(Amd64Register &dst, Amd64Register &src, ConflictStrategy strategy);
        void MoveValue(Amd64Register &dst, Value &value, ConflictStrategy strategy);

        void HandleConflict(Amd64Register &reg, ConflictStrategy strategy);

        [[nodiscard]] StackAllocationContainer &AcquireStackSpace(std::size_t size);
        [[nodiscard]] Amd64Register &AcquireGPRegister(Amd64RegisterValueType value_type = Amd64RegisterValueType::Integer);

        void Associate(Value &value, Container &container);

        void Insert(Amd64Instruction &&inst);
        void InsertProlog(Amd64Instruction &&inst);

    public:
        Amd64Module &module;
        Amd64Function function;
        IRFunction &ir_function;
        Amd64RegisterBank registers;
        std::int64_t stack_depth = 0;
        std::vector<std::unique_ptr<StackAllocationContainer>> local_swap_;

        [[nodiscard]] Amd64Function Translate();

        explicit Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function);
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
