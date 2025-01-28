
#include "Amd64Register.h"

using namespace city;

Amd64RegisterCode Amd64Register::GetCode() const noexcept
{
    return this->code_;
}

void Amd64Register::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, this);
}

Amd64Register::Amd64Register(Amd64RegisterCode code) : code_(code) {}
