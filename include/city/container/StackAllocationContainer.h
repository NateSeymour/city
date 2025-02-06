#ifndef STACKALLOCATIONCONTAINER_H
#define STACKALLOCATIONCONTAINER_H

#include <cstddef>
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
        std::size_t base_offset_ = 0;

    public:
        void Load(Amd64FunctionTranslator &translator, Amd64Register &dst) override;
        void Store(Amd64FunctionTranslator &translator, Amd64Register &src) override;

        void SetOffset(std::size_t offset);
        [[nodiscard]] std::size_t GetOffset() const noexcept;
        [[nodiscard]] std::size_t GetSize() const noexcept;

        StackAllocationContainer(std::size_t size);
    };
} // namespace city

#endif // STACKALLOCATIONCONTAINER_H
