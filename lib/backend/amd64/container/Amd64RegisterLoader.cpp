#include <city/backend/amd64/Amd64Translator.h>
#include <city/backend/amd64/container/Amd64RegisterLoader.h>
#include <city/backend/amd64/instruction/memory/Amd64Mov.h>

using namespace city;

void Amd64RegisterLoader::Load(Amd64Register &target, ConstantDataContainer *container)
{
    Stub stub{
            .src_offset = container->GetOffset(),
            .type = StubSourceLocation::Data,
    };

    this->translator.module.Insert(Amd64Mov::OIS(target.GetCode(), std::move(stub)));

    auto value_type = container->GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->translator.module.Insert(Amd64Mov::RMX(target.GetCode(), target.GetCode(), container->GetSize(), Amd64Mod::Memory));
    }
    else
    {
        this->translator.module.Insert(Amd64Mov::SDA(target.GetCode(), target.GetCode(), Amd64Mod::Memory));
    }
}

void Amd64RegisterLoader::Load(Amd64Register &target, Amd64Register *container)
{
    this->translator.module.Insert(Amd64Mov::MR64(target.GetCode(), container->GetCode()));
}
