#include <city/backend/amd64/container/Amd64Register.h>

using namespace city;

Amd64RegisterCode Amd64Register::GetCode() const noexcept
{
    return this->code_;
}

void Amd64Register::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, this);
}

Amd64Register::Amd64Register(std::uint8_t code, Amd64RegisterValueType value_type, Amd64RegisterType type, bool ext) :
    code_(code), value_type_(value_type), type_(type), is_ext_(ext)
{
}
