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
}

void Amd64RegisterLoader::Load(Amd64Register &target, Amd64Register *container)
{
    this->translator.module.Insert(Amd64Mov::MR64(target.GetCode(), container->GetCode()));
}
