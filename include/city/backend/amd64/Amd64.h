#ifndef X86_64_H
#define X86_64_H

#include <city/backend/Backend.h>

namespace city
{
    class Amd64 : public Backend
    {
    public:
        [[nodiscard]] Object BuildIRModule(IRModule &&ir_module) override;
    };
} // namespace city

#endif // X86_64_H
