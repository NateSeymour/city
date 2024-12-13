#ifndef CITY_POINTERVALUE_H
#define CITY_POINTERVALUE_H

#include "Value.h"

namespace city
{
    class PointerValue : public Value
    {
        PointerValue() : Value(Type()) {}
    };
} // city

#endif //CITY_POINTERVALUE_H
