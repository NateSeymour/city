#include "IRModule.h"

using namespace city;

std::string const &IRModule::GetName() const noexcept
{
    return this->name_;
}

IRBuilder IRModule::CreateBuilder() noexcept
{
    return IRBuilder(*this);
}

IRModule::IRModule(std::string name) : name_(std::move(name)) {}
