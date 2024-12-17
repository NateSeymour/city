#include "Module.h"

using namespace city;

Builder Module::CreateBuilder() noexcept
{
    return Builder(*this);
}

std::unique_ptr<Module> Module::Create(std::string name)
{
    return std::make_unique<Module>(std::move(name));
}

Module::Module(std::string name) : name_(std::move(name)) {}
