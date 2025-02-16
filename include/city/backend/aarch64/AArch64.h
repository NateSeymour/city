#ifndef CITY_AARCH64_H
#define CITY_AARCH64_H

#include "city/backend/Backend.h"

namespace city
{
    class AArch64 : public Backend
    {
    public:
        NativeModule BuildIRModule(IRModule &&ir_module) override;
    };
} // namespace city

#endif // CITY_AARCH64_H
