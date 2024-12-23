#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include "ir/Container.h"
#include "ir/type/Type.h"

namespace city
{
    class Value
    {
        Type type_;
        StorageClass storage_class_;

        Container *container_ = nullptr;

        std::size_t read_count_ = 0;
        std::size_t write_count_ = 0;

    public:
        void IncrementReadCount() noexcept;
        void IncrementWriteCount() noexcept;

        [[nodiscard]] Type GetType() const noexcept;

        [[nodiscard]] bool IsConstant() const noexcept;
        [[nodiscard]] bool IsUsed() const noexcept;
        [[nodiscard]] virtual bool IsCompileTimeConstant() const noexcept;

        explicit Value(Type type, StorageClass storage_class = StorageClass::Temporary);
        virtual ~Value() = default;
    };
} // namespace city

#endif // CITY_VALUE_H
