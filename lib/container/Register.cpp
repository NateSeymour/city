#include "city/container/Register.h"
#include "city/backend/IRTranslator.h"

using namespace city;

void Register::Load(IRTranslator &translator, Register &dst)
{
    translator.Load(dst, *this);
}

void Register::Store(IRTranslator &translator, Register &src)
{
    translator.Store(*this, src);
}

RegisterCode Register::GetCode() const noexcept
{
    return this->code_;
}

RegisterPurpose Register::GetRegisterType() const noexcept
{
    return this->type_;
}

Volatility Register::GetVolatility() const noexcept
{
    return this->volatility_;
}

bool Register::IsExtension() const noexcept
{
    return this->is_ext_;
}

RegisterType Register::GetValueType() const noexcept
{
    return this->value_type_;
}

size_t Register::GetSize() const noexcept
{
    switch (this->value_type_)
    {
        case RegisterType::Integer:
        {
            return 8;
        }

        case RegisterType::FloatingPoint:
        {
            return 16;
        }
    }
}

ContainerType Register::GetType() const noexcept
{
    return ContainerType::Register;
}
