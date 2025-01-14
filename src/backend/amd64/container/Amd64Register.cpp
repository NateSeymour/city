
#include "Amd64Register.h"

using namespace city;

Amd64RegisterCode Amd64Register::GetCode() const noexcept
{
    return this->code_;
}

Amd64Register::Amd64Register(Amd64RegisterCode code) : code_(code) {}
