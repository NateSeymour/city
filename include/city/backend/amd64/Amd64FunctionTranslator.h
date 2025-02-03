#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <city/backend/IRTranslator.h>
#include <city/backend/amd64/container/Amd64RegisterLoader.h>
#include "Amd64Function.h"
#include "Amd64Module.h"
#include "container/Amd64RegisterBank.h"

namespace city
{
    enum class ConflictStrategy
    {
        Push,
        PreferMoveToUnused,
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
        friend class Amd64RegisterLoader;

    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(FAddInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

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
         * Moves value and transfers its ownership.
         * @param value
         * @param reg
         * @param strategy
         * @return
         */
        [[nodiscard]] Amd64Register *MoveValue(Value &value, Amd64Register &reg, ConflictStrategy strategy);

        [[nodiscard]] Amd64Register *InstantiateValue(Value &value, Amd64Register &reg, ConflictStrategy strategy);

        [[nodiscard]] Amd64Register &FindUnusedGPRegister(Amd64RegisterValueType value_type = Amd64RegisterValueType::Integer);

        void Insert(Amd64Instruction &&inst);

    public:
        Amd64Module &module;
        Amd64Function function;
        IRFunction &ir_function;
        Amd64RegisterLoader register_loader{*this};
        Amd64RegisterBank registers;

        [[nodiscard]] Amd64Function Translate();

        explicit Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function);
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
