#ifndef CITY_CONTAINER_H
#define CITY_CONTAINER_H

#include <city/backend/amd64/container/Amd64RegisterLoader.h>

namespace city
{
    class Value;

    class Container
    {
    protected:
        Value *value_ = nullptr;

    public:
        void AssociateValue(Value *value);
        void Disassociate();
        [[nodiscard]] Value *GetValue() const noexcept;
        [[nodiscard]] bool HasValue() const noexcept;

        virtual void Load(Amd64FunctionTranslator &translator, Amd64Register &dst) = 0;
        virtual void Store(Amd64FunctionTranslator &translator, Amd64Register &src) = 0;

        virtual ~Container() = default;
    };
} // namespace city

#endif // CITY_CONTAINER_H
