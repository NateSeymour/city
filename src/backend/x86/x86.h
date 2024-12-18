#ifndef X86_64_H
#define X86_64_H

#include <array>
#include <cstdint>
#include "backend/Backend.h"
#include "x86Register.h"

namespace city
{
    class x86 : public Backend
    {
        std::array<x86Register, 8> registers_;

    public:
        [[nodiscard]] Object BuildModule(Module &module) override;

        x86();
    };
} // namespace city

#endif // X86_64_H
