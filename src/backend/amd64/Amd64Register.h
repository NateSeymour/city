#ifndef CITY_X86REGISTER_H
#define CITY_X86REGISTER_H

#include "Amd64ModRM.h"
#include "ir/Container.h"

namespace city
{
    class Amd64Register : public Container
    {
        Amd64RegisterCode code_;

    public:
        Amd64Register(Amd64RegisterCode code);
    };
} // namespace city

#endif // CITY_X86REGISTER_H
