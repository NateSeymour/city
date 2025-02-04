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
        void LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target) override;

        StackAllocationContainer(std::size_t size);
    };
} // namespace city

#endif // STACKALLOCATIONCONTAINER_H
