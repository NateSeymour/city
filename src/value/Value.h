#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include <vector>
#include "Container.h"
#include "type/Type.h"

namespace city
{
    class Value
    {
        Type type_;
        StorageClass storage_class_;

        Container *container_ = nullptr;

        std::size_t read_count_ = 0;

    public:
        void IncrementReadCount() noexcept;
        void DecrementReadCount() noexcept;

        void SetContainer(Container *container);

        [[nodiscard]] Type GetType() const noexcept;

        [[nodiscard]] bool IsInstantiated() const noexcept;
        [[nodiscard]] bool IsUsed() const noexcept;
        [[nodiscard]] virtual bool IsCompileTimeConstant() const noexcept;
        [[nodiscard]] virtual std::vector<std::byte> const &GetDataBuffer() const;

        explicit Value(Type type, StorageClass storage_class = StorageClass::Temporary);
        virtual ~Value() = default;
    };
} // namespace city

#endif // CITY_VALUE_H
