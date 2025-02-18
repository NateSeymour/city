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

std::size_t Register::GetSize() const noexcept
{
    return 8;
}

ContainerType Register::GetType() const noexcept
{
    return ContainerType::Register;
}
