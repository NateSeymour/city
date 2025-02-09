#ifndef CITY_CONTAINER_H
#define CITY_CONTAINER_H

#include <cstddef>

namespace city
{
    class Value;
    class Amd64FunctionTranslator;
    class Amd64Register;

    enum class ContainerType
    {
        Constant,
        StackAllocation,
        Register,
    };

    class Container
    {
    protected:
        Value *value_ = nullptr;

    public:
        void AssociateValue(Value *value);
        void Disassociate();
        [[nodiscard]] Value *GetValue() const noexcept;
        [[nodiscard]] bool HasValue() const noexcept;

        [[nodiscard]] virtual std::size_t GetSize() const noexcept = 0;

        [[nodiscard]] virtual ContainerType GetType() const noexcept = 0;

        virtual void Load(Amd64FunctionTranslator &translator, Amd64Register &dst) = 0;
        virtual void Store(Amd64FunctionTranslator &translator, Amd64Register &src) = 0;

        virtual ~Container() = default;
    };
} // namespace city

#endif // CITY_CONTAINER_H
