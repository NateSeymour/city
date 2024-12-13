#ifndef CITY_CONTAINER_H
#define CITY_CONTAINER_H

namespace city
{
    enum class StorageClass
    {
        Temporary,
        Constant,
        StackPreferred,
        HeapPreferred,
        StaticPreferred,
    };

    class Container
    {

    };
} // city

#endif //CITY_CONTAINER_H
