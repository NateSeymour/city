#ifndef NATIVEINSTRUCTION_H
#define NATIVEINSTRUCTION_H

#include <city/Symbol.h>
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

        /**
         * The linker reference is an optional flag for the linker to resolve the named symbol that is pointed to.
         * After Assembly creation, the linker will make a pass to fill in final pointer values.
         */
        std::optional<Stub> stub_ = std::nullopt;

    public:
        void SetLabel(std::string name);
        [[nodiscard]] char const *GetLabel() const noexcept;

        void SetStub(Stub stub);
        [[nodiscard]] bool HasStub() const noexcept;
        [[nodiscard]] Stub const &GetStub() const;
        [[nodiscard]] virtual std::size_t GetStubOffset() = 0;

        [[nodiscard]] virtual std::size_t GetBinarySize() const noexcept = 0;
        [[nodiscard]] virtual std::size_t WriteToBuffer(std::byte *buffer) const = 0;

        virtual ~NativeInstruction() = default;
    };
} // namespace city

#endif // NATIVEINSTRUCTION_H
