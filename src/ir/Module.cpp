#include "Module.h"

using namespace city;

Builder Module::CreateBuilder() noexcept
{
    return Builder(*this);
}

Module::Module(std::string name) : name_(std::move(name)) {}
