#include <city/backend/amd64/container/Amd64Register.h>

using namespace city;

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

void Amd64Register::Touch() noexcept
{
    this->touched_ = true;
}

bool Amd64Register::IsTouched() const noexcept
{
    return this->touched_;
}

void Amd64Register::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, *this);
}
