#ifndef X86_64_H
#define X86_64_H

#include "Amd64Register.h"
#include "backend/Backend.h"

namespace city
{
    extern std::array<Amd64Register, 8> const amd64_register_definitions;

    class Amd64 : public Backend
    {
    public:
        [[nodiscard]] Object BuildModule(IRModule &ir_module) override;
    };
} // namespace city

#endif // X86_64_H
