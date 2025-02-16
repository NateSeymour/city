#include "city/backend/aarch64/AArch64Module.h"

using namespace city;

Object AArch64Module::Compile()
{

    return {std::move(this->data_), std::move(text), std::move(symtab), std::move(this->stubs_)};
}

AArch64Module::AArch64Module(std::string name, std::vector<std::uint8_t> cdata) : NativeModule(std::move(name), std::move(cdata)) {}
