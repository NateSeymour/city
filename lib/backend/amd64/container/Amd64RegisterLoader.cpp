#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/backend/amd64/container/Amd64RegisterLoader.h>
#include <city/backend/amd64/instruction/memory/Amd64Mov.h>

using namespace city;

void Amd64RegisterLoader::Load(Amd64Register &target, ConstantDataContainer &container)
{
    Stub stub{
            .src_offset = container.GetOffset(),
            .type = StubSourceLocation::Data,
    };

    this->translator.Insert(Amd64Mov::OIS(target.GetCode(), std::move(stub)));

    auto value_type = container.GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->translator.Insert(Amd64Mov::RMX(target.GetCode(), target.GetCode(), container.GetSize(), Amd64RegisterAccessType::Pointer));
    }
    else
    {
        this->translator.Insert(Amd64Mov::SDA(target.GetCode(), target.GetCode(), Amd64RegisterAccessType::Pointer));
    }
}

void Amd64RegisterLoader::Load(Amd64Register &target, Amd64Register &container)
{
    /* Do nothing, because value is already in register */
}

void Amd64RegisterLoader::Load(Amd64Register &target, StackAllocationContainer &container) {}
