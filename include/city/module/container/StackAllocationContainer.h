#ifndef STACKALLOCATIONCONTAINER_H
#define STACKALLOCATIONCONTAINER_H

#include <cstddef>
#include <cstdint>
#include "Container.h"

namespace city
{
    class StackAllocationContainer : public Container
    {
        /**
         * Size of allocated space.
         */
        std::size_t size_ = 0;

        /**
         * Offset to the stack base of the current frame.
         */
        std::int64_t base_offset_ = 0;

    public:
        void Load(IRTranslator &translator, Register &dst) override;
        void Store(IRTranslator &translator, Register &src) override;

        void SetOffset(std::int64_t offset);
        [[nodiscard]] std::int64_t GetOffset() const noexcept;
        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] ContainerType GetType() const noexcept override;

        StackAllocationContainer(std::size_t size);
        StackAllocationContainer(StackAllocationContainer const &) = delete;
    };
} // namespace city

#endif // STACKALLOCATIONCONTAINER_H
