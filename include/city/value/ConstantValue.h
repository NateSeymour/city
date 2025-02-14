#ifndef CONSTANTVALUE_H
#define CONSTANTVALUE_H

#include "Value.h"
#include "city/container/ConstantDataContainer.h"

namespace city
{
    /**
     * Value specialization for holding compile-time constants.
     */
    class ConstantValue : public Value
    {
        ConstantDataContainer data_container_;

    public:
        [[nodiscard]] Container *GetContainer() noexcept override;

        void IncrementReadCount() noexcept override;
        void DecrementReadCount() noexcept override;
        [[nodiscard]] std::size_t GetReadCount() const noexcept override;

        [[nodiscard]] bool IsInstantiated() const noexcept override;
        [[nodiscard]] bool IsUsed() const noexcept override;

        bool Release() override;

        ConstantValue(Type type, ConstantDataContainer container);
    };
} // namespace city

#endif // CONSTANTVALUE_H
