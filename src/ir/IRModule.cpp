#include "IRModule.h"

using namespace city;

Builder IRModule::CreateBuilder() noexcept
{
    return Builder(*this);
}

IRModule::IRModule(std::string name) : name_(std::move(name)) {}
