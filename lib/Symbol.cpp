#include <city/Symbol.h>

using namespace city;

bool Stub::IsAnonymous() const noexcept
{
    return !this->label.has_value();
}
