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
    protected:
        Value *value_ = nullptr;

    public:
        void SetValue(Value *value);
        [[nodiscard]] Value *GetValue() const noexcept;
        [[nodiscard]] bool HasValue() const noexcept;

        virtual ~Container() = default;
    };
} // namespace city

#endif // CITY_CONTAINER_H
