#ifndef X86_64_H
#define X86_64_H

#include "backend/Backend.h"

namespace city
{
    class Amd64 : public Backend
    {
    public:
        [[nodiscard]] NativeModule BuildModule(IRModule &module) override;
    };
} // namespace city

#endif // X86_64_H
