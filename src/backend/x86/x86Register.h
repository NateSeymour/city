#ifndef CITY_X86REGISTER_H
#define CITY_X86REGISTER_H

#include "ir/Container.h"
#include "x86ModRM.h"

namespace city
{
    class x86Register : public Container
    {
        x86RegisterCode code_;

    public:
        x86Register(x86RegisterCode code);
    };
} // namespace city

#endif // CITY_X86REGISTER_H
