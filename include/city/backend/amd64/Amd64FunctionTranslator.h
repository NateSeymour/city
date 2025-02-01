#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <city/backend/IRTranslator.h>
#include <city/backend/amd64/container/Amd64RegisterLoader.h>
#include <city/ir/instruction/InstructionFunctor.h>
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
    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(FAddInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

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

        [[nodiscard]] Amd64Register *FindUnusedRegister() noexcept;

    public:
        IRFunction &ir_function;
        Amd64RegisterLoader register_loader{*this};
        Amd64RegisterBank registers;

        explicit Amd64FunctionTranslator(Amd64Module &module) : module(module) {}
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
