#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include <optional>
#include <string>
#include "city/container/Container.h"
#include "city/type/Type.h"

namespace city
{
    class Function;

    class Value
    {
        friend class Container;

    protected:
        std::optional<std::string> name_;
        Type type_;
        Container *container_ = nullptr;

        std::size_t read_count_ = 0;

    public:
        [[nodiscard]] Function *ToFunction() noexcept;

        [[nodiscard]] std::optional<std::string> const &GetName() const noexcept;
        [[nodiscard]] Type const &GetType() const noexcept;
        [[nodiscard]] virtual Container *GetContainer() noexcept;

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

        Value(Type type);
        Value(std::string name, Type type);

        virtual ~Value() = default;
    };
} // namespace city

#endif // CITY_VALUE_H
