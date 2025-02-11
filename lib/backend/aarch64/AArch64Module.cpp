#include "city/backend/aarch64/AArch64Module.h"

using namespace city;

Object AArch64Module::Compile() {}

AArch64Module::AArch64Module(std::string name, std::vector<std::uint8_t> data) : NativeModule(std::move(name), std::move(data)) {}
