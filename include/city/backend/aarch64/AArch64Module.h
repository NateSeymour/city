#ifndef AARCH64MODULE_H
#define AARCH64MODULE_H

#include <vector>
#include "city/backend/NativeModule.h"
#include "city/backend/aarch64/AArch64Function.h"

namespace city
{
    class AArch64;

    class AArch64Module : public NativeModule
    {
        friend class AArch64;

    protected:
        std::vector<AArch64Function> functions_;

    public:
        [[nodiscard]] Object Compile() override;

        AArch64Module(std::string name, std::vector<std::uint8_t> data);
    };
} // namespace city

#endif // AARCH64MODULE_H
