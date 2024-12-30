#ifndef CITY_AMD64BUILDER_H
#define CITY_AMD64BUILDER_H

#include "Amd64.h"
#include "Amd64Module.h"

namespace city
{
    enum class Amd64RegisterConflictStrategy
    {
        Push,
        MoveToUnused,
        Discard,
    };

    enum class Amd64ReturnType
    {
        Near,
        Far,
    };

    class Amd64Builder
    {
        Amd64Module &module_;

        std::array<Amd64Register, 8> registers_ = amd64_register_definitions;

    public:
        void InsertReturnInst(Amd64ReturnType return_type = Amd64ReturnType::Near);
        void InsertPopInst(Amd64RegisterCode reg);

        [[nodiscard]] Amd64Register *MoveValueToUnusedRegister(Value *value);
        Amd64Register *MoveValueToRegister(Value *value, Amd64RegisterCode reg, Amd64RegisterConflictStrategy conflict_strategy);

        explicit Amd64Builder(Amd64Module &module);
    };
} // namespace city

#endif // CITY_AMD64BUILDER_H
