#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/backend/amd64/container/Amd64Register.h>

using namespace city;

void Amd64Register::Load(Amd64FunctionTranslator &translator, Amd64Register &dst)
{
    translator.Load(dst, *this);
}

void Amd64Register::Store(Amd64FunctionTranslator &translator, Amd64Register &src)
{
    translator.Load(*this, src);
}

Amd64RegisterCode Amd64Register::GetCode() const noexcept
{
    return this->code_;
}

Amd64RegisterType Amd64Register::GetType() const noexcept
{
    return this->type_;
}

Amd64RegisterVolatility Amd64Register::GetVolatility() const noexcept
{
    return this->volatility_;
}

bool Amd64Register::IsExtension() const noexcept
{
    return this->is_ext_;
}

Amd64RegisterValueType Amd64Register::GetValueType() const noexcept
{
    return this->value_type_;
}
