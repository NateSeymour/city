#ifndef CITY_X86REGISTER_H
#define CITY_X86REGISTER_H

#include <city/container/Container.h>
#include <cstdint>

namespace city
{
    /**
     * The type of register determines the bank of registers to be referenced.
     * Integer: R0-R15
     * FloatingPoint: XMM0-XMM15
     */
    enum class Amd64RegisterValueType
    {
        Integer,
        FloatingPoint,
    };

    enum class Amd64RegisterType
    {
        GeneralPurpose,
        Special,
    };

    /**
     * Determines the type of access made to into the register.
     * If Pointer, then the value in the register will be treated as a pointer. Instructions will load value from memory location held in pointer.
     * If Value, then the value in the register will be treated as a value.
     */
    enum class Amd64RegisterAccessType : std::uint8_t
    {
        Pointer = 0x0,
        Value = 0x3,
    };

    using Amd64RegisterCode = std::uint8_t;

    class Amd64Register : public Container
    {
    protected:
        Amd64RegisterCode code_;
        Amd64RegisterValueType value_type_;
        Amd64RegisterType type_;
        bool is_ext_ = false;

    public:
        [[nodiscard]] Amd64RegisterCode GetCode() const noexcept;

        void LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target) override;

        constexpr Amd64Register(Amd64RegisterCode code, Amd64RegisterValueType value_type, Amd64RegisterType type = Amd64RegisterType::GeneralPurpose, bool ext = false);
    };
} // namespace city

#endif // CITY_X86REGISTER_H
