#include "Amd64RegisterLoader.h"

#include "backend/amd64/Amd64Translator.h"
#include "backend/amd64/instruction/memory/Amd64Mov.h"

using namespace city;

void Amd64RegisterLoader::Load(Amd64Register &target, ConstantDataContainer *container)
{
    this->translator.module.Insert(Amd64Mov::OIX(target.GetCode(), container->GetData()));
}

void Amd64RegisterLoader::Load(Amd64Register &target, Amd64Register *container)
{
    this->translator.module.Insert(Amd64Mov::MR64(target.GetCode(), container->GetCode()));
}
