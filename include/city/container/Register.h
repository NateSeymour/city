#ifndef CITY_REGISTER_H
#define CITY_REGISTER_H

#include <cstdint>
#include <stdexcept>

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

    struct RegisterGuard;

    class Register : public Container
    {
        friend struct RegisterGuard;

    protected:
        RegisterCode code_;
        RegisterType value_type_;
        Volatility volatility_;
        RegisterPurpose type_;
        bool is_ext_ = false;

        bool locked_ = false;

        void Lock()
        {
            this->locked_ = true;
        }

        void Unlock()
        {
            this->locked_ = false;
        }

    public:
        void Load(IRTranslator &translator, Register &dst) override;
        void Store(IRTranslator &translator, Register &src) override;

        [[nodiscard]] RegisterCode GetCode() const noexcept;
        [[nodiscard]] RegisterType GetValueType() const noexcept;
        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] RegisterPurpose GetRegisterPurpose() const noexcept;
        [[nodiscard]] ContainerType GetType() const noexcept override;
        [[nodiscard]] Volatility GetVolatility() const noexcept;
        [[nodiscard]] bool IsExtension() const noexcept;
        [[nodiscard]] bool IsLocked() const noexcept;

        constexpr Register(RegisterCode code, RegisterType value_type, Volatility volatility, RegisterPurpose type = RegisterPurpose::General, bool ext = false) :
            code_(code), value_type_(value_type), volatility_(volatility), type_(type), is_ext_(ext)
        {
        }

        Register(Register const &) = delete;
    };

    struct RegisterGuard
    {
        Register &reg;

        RegisterGuard(RegisterGuard const &) = delete;

        RegisterGuard(RegisterGuard &&) = default;

        RegisterGuard(Register &reg) : reg(reg)
        {
            if (reg.locked_)
            {
                throw std::runtime_error("failed to lock register");
            }

            reg.Lock();
        }

        ~RegisterGuard()
        {
            reg.Unlock();
        }
    };
} // namespace city

#endif // CITY_REGISTER_H
