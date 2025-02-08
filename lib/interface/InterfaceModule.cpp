#include <city/interface/InterfaceModule.h>

using namespace city;

std::string const &InterfaceModule::GetName() const noexcept
{
    return this->name_;
}
