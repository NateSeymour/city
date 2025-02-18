#ifndef CITY_REGISTER_H
#define CITY_REGISTER_H

#include <cstdint>
#include "Container.h"

namespace city
{
    enum class RegisterType
    {
        Integer,
        FloatingPoint,
    };

    enum class RegisterPurpose
    {
        General,
        Special,
    };

    enum class Volatility
    {
        Volatile,
        NonVolatile,
    };

    using RegisterCode = std::uint8_t;

    class Register : public Container
    {
    protected:
        RegisterCode code_;
        RegisterType value_type_;
        Volatility volatility_;
        RegisterPurpose type_;
        bool is_ext_ = false;

    public:
        void Load(IRTranslator &translator, Register &dst) override;
        void Store(IRTranslator &translator, Register &src) override;

        [[nodiscard]] RegisterCode GetCode() const noexcept;
        [[nodiscard]] RegisterType GetValueType() const noexcept;
        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] RegisterPurpose GetRegisterType() const noexcept;
        [[nodiscard]] ContainerType GetType() const noexcept override;
        [[nodiscard]] Volatility GetVolatility() const noexcept;
        [[nodiscard]] bool IsExtension() const noexcept;

        constexpr Register(RegisterCode code, RegisterType value_type, Volatility volatility, RegisterPurpose type = RegisterPurpose::General, bool ext = false) :
            code_(code), value_type_(value_type), volatility_(volatility), type_(type), is_ext_(ext)
        {
        }

        Register(Register const &) = delete;
    };
} // namespace city

#endif // CITY_REGISTER_H
