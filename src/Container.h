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

    class Value;

    class Container
    {
        Value *value_ = nullptr;

    public:
        virtual ~Container() = default;
    };
} // namespace city

#endif // CITY_CONTAINER_H
