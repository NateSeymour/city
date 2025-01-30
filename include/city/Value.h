#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include <vector>
#include "container/Container.h"
#include "type/Type.h"

namespace city
{
    class Value
    {
        Type type_;

        Container *container_ = nullptr;

        std::size_t read_count_ = 0;

    public:
        void IncrementReadCount() noexcept;
        void DecrementReadCount() noexcept;

        void AssociateContainer(Container *container);
        void Disassociate();

        [[nodiscard]] Container *GetContainer() const noexcept;

        [[nodiscard]] Type GetType() const noexcept;

        [[nodiscard]] bool IsInstantiated() const noexcept;
        [[nodiscard]] bool IsUsed() const noexcept;

        explicit Value(Type type);
    };
} // namespace city

#endif // CITY_VALUE_H
