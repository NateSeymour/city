#ifndef AMD64CONTAINERFUNCTOR_H
#define AMD64CONTAINERFUNCTOR_H

#include "Amd64Register.h"

namespace city
{
    struct Amd64ContainerFunctor
    {
        void Visit(Amd64Register *reg);
    };
} // namespace city

#endif // AMD64CONTAINERFUNCTOR_H
