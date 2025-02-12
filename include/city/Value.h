#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include <vector>
#include "container/Container.h"
#include "type/Type.h"

namespace city
{
    class Function;

    class Value
    {
        friend class Container;

    protected:
        Type type_;

        Container *container_ = nullptr;

        std::size_t read_count_ = 0;

    public:
        /**
         * Attempts to release the Value by clearing its container. Fails if Value is still used.
         * @return True if successful, else false
         */
        bool Release();

        [[nodiscard]] Function *ToFunction() noexcept;

        [[nodiscard]] std::size_t GetReadCount() const noexcept;

        void IncrementReadCount() noexcept;
        void DecrementReadCount() noexcept;

        [[nodiscard]] Container *GetContainer() const noexcept;

        [[nodiscard]] Type const &GetType() const noexcept;

        [[nodiscard]] bool IsInstantiated() const noexcept;
        [[nodiscard]] bool IsUsed() const noexcept;

        explicit Value(Type type);
        virtual ~Value() = default;
    };
} // namespace city

#endif // CITY_VALUE_H
