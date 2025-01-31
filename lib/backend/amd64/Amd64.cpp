#include <city/backend/amd64/Amd64.h>
#include <city/backend/amd64/Amd64Translator.h>
#include <city/ir/block/IRBlock.h>

using namespace city;

std::array<Amd64Register, 8> const city::amd64_register_definitions = {
        Amd64Register(Amd64RegisterCode::XMM0),
        Amd64Register(Amd64RegisterCode::XMM1),
        Amd64Register(Amd64RegisterCode::XMM2),
        Amd64Register(Amd64RegisterCode::XMM3),
        Amd64Register(Amd64RegisterCode::XMM4),
        Amd64Register(Amd64RegisterCode::XMM5),
        Amd64Register(Amd64RegisterCode::XMM6),
        Amd64Register(Amd64RegisterCode::XMM7),
};

Object Amd64::BuildModule(IRModule &ir_module)
{
    Amd64Module amd64_module{ir_module};

    return amd64_module.Compile();
}
