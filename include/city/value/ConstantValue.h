#ifndef CONSTANTVALUE_H
#define CONSTANTVALUE_H

#include "Value.h"
#include "city/container/ConstantDataContainer.h"

namespace city
{
    /**
     * Value specialization for holding compile-time constants.
     */
    class ConstantValue : public Value
    {
        ConstantDataContainer data_container_;

    public:
        ConstantValue(Type type, ConstantDataContainer container);
    };
} // namespace city

#endif // CONSTANTVALUE_H
