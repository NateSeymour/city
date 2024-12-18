#ifndef NATIVEINSTRUCTION_H
#define NATIVEINSTRUCTION_H

#include <cstddef>

namespace city
{
    class NativeInstruction
    {
    public:
        [[nodiscard]] virtual std::size_t GetBinarySize() const noexcept = 0;
        [[nodiscard]] virtual std::size_t WriteToBuffer(std::byte *buffer) const = 0;

        virtual ~NativeInstruction() = default;
    };
} // namespace city

#endif // NATIVEINSTRUCTION_H
