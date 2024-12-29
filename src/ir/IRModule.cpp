#include "IRModule.h"

using namespace city;

std::string const &IRModule::GetName() const noexcept
{
    return this->name_;
}

Builder IRModule::CreateBuilder() noexcept
{
    return Builder(*this);
}

IRModule::IRModule(std::string name) : name_(std::move(name)) {}
