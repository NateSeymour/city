#ifndef NATIVEINSTRUCTION_H
#define NATIVEINSTRUCTION_H

#include <city/Symbol.h>
#include <cstddef>
#include <cstdint>

namespace city
{
    class NativeInstruction
    {
    public:
        [[nodiscard]] virtual std::size_t GetBinarySize() const noexcept = 0;
        virtual std::size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) = 0;

        virtual ~NativeInstruction() = default;
    };
} // namespace city

#endif // NATIVEINSTRUCTION_H
