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

    class Amd64FunctionTranslator : IRTranslator
    {
        friend class ConstantDataContainer;
        friend class StackAllocationContainer;
        friend class Amd64Register;

        std::uint64_t register_dislocation_count_ = 0;

    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        void Load(Amd64Register &dst, ConstantDataContainer &src);
        void Load(Amd64Register &dst, StackAllocationContainer &src);
        void Load(Amd64Register &dst, Amd64Register &src);

        void Store(StackAllocationContainer &dst, Amd64Register &src);

        template<typename IRInstructionType, typename NativeInstructionType>
            requires requires(NativeInstructionType) {
                NativeInstructionType::MR64;
                NativeInstructionType::SDA;
            }
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto dsttmp = this->LoadValue(inst.GetLHS());
            auto srctmp = this->LoadValue(inst.GetRHS());

            Type optype = inst.GetLHS()->GetType();
            if (optype.GetNativeType() == NativeType::Integer)
            {
                this->function.text_.push_back(NativeInstructionType::MR64(dsttmp->GetCode(), srctmp->GetCode()));
            }
            else
            {
                this->function.text_.push_back(NativeInstructionType::SDA(dsttmp->GetCode(), srctmp->GetCode()));
            }

            (void)this->InstantiateValue(*inst.GetReturnValue(), *dsttmp, ConflictStrategy::Discard);

            inst.GetLHS()->DecrementReadCount();
            inst.GetRHS()->DecrementReadCount();
        }

        /**
         * Loads a value into a register without transferring its ownership.
         * @param value
         * @param reg
         * @param strategy
         * @param load_type
         * @return
         */
        [[nodiscard]] Amd64Register *LoadValue(
                Value *value, Amd64Register *reg = nullptr, ConflictStrategy strategy = ConflictStrategy::Push, LoadType load_type = LoadType::Value);


        /**
         * Moves value into container, transferring its ownership.
         * @param value
         * @param dst
         * @param strategy
         */
        void MoveValue(Value &value, Container &dst, ConflictStrategy strategy);

        void InstantiateValue(Value &value, Amd64Register &reg);

        [[nodiscard]] StackAllocationContainer &AcquireStackSpace(std::size_t size);
        [[nodiscard]] Amd64Register &AcquireGPRegister(Amd64RegisterValueType value_type = Amd64RegisterValueType::Integer);

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
