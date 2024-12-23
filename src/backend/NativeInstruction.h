#ifndef NATIVEINSTRUCTION_H
#define NATIVEINSTRUCTION_H

#include <cstddef>
#include <optional>
#include <string>

namespace city
{
    class NativeInstruction
    {
        /**
         * Later it would be good for this to become a SymbolDef-like thing that holds type information as well.
         */
        std::optional<std::string> label_ = std::nullopt;

    public:
        void SetLabel(std::string name);
        [[nodiscard]] char const *GetLabel() const noexcept;

        [[nodiscard]] virtual std::size_t GetBinarySize() const noexcept = 0;
        [[nodiscard]] virtual std::size_t WriteToBuffer(std::byte *buffer) const = 0;

        virtual ~NativeInstruction() = default;
    };
} // namespace city

#endif // NATIVEINSTRUCTION_H
