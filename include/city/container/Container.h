#ifndef CITY_CONTAINER_H
#define CITY_CONTAINER_H

#include <cstddef>

namespace city
{
    class Value;
    class Register;
    class IRTranslator;

    enum class ContainerType
    {
        Constant,
        StackAllocation,
        Register,
    };

    class Container
    {
        friend class Value;

    protected:
        Value *value_ = nullptr;

    public:
        /**
         * Tries to place new value in container, but will fail if it is already holding a valid value.
         * @param value New value to hold in the container
         * @return True if successful, else false
         */
        bool InstantiateValue(Value *value);

        bool TakeValue(Container *container);

        [[nodiscard]] bool HasValue() const noexcept;
        [[nodiscard]] Value *GetValue() const noexcept;

        [[nodiscard]] virtual std::size_t GetSize() const noexcept = 0;

        [[nodiscard]] virtual ContainerType GetType() const noexcept = 0;

        virtual void Load(IRTranslator &translator, Register &dst) = 0;
        virtual void Store(IRTranslator &translator, Register &src) = 0;

        virtual ~Container() = default;
    };
} // namespace city

#endif // CITY_CONTAINER_H
