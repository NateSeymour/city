#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include "Amd64Module.h"
#include "backend/IRTranslator.h"
#include "container/Amd64RegisterLoader.h"
#include "ir/instruction/InstructionFunctor.h"

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

    struct Amd64Translator : IRTranslator
    {
        Amd64Module &module;
        Amd64RegisterLoader register_loader{*this};

        std::array<Amd64Register, 8> registers_ = amd64_register_definitions;

        [[nodiscard]] Amd64Register *GetRegisterByCode(Amd64RegisterCode code);

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

        IRTranslationResult Translate(AddInst *instruction) override;
        IRTranslationResult Translate(SubInst *instruction) override;
        IRTranslationResult Translate(CallInst *instruction) override;
        IRTranslationResult Translate(RetInst *instruction) override;

        explicit Amd64Translator(Amd64Module &module) : module(module) {}
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
