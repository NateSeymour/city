#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include "city/container/Container.h"
#include "city/type/Type.h"

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
        [[nodiscard]] Function *ToFunction() noexcept;

        [[nodiscard]] virtual Container *GetContainer() noexcept;
        [[nodiscard]] Type const &GetType() const noexcept;

        virtual void IncrementReadCount() noexcept;
        virtual void DecrementReadCount() noexcept;
        [[nodiscard]] virtual std::size_t GetReadCount() const noexcept;

        [[nodiscard]] virtual bool IsInstantiated() const noexcept;
        [[nodiscard]] virtual bool IsUsed() const noexcept;

        /**
         * Attempts to release the Value by clearing its container. Fails if Value is still used.
         * @return True if successful, else false
         */
        virtual bool Release();

        explicit Value(Type type);
        virtual ~Value() = default;
    };
} // namespace city

#endif // CITY_VALUE_H
