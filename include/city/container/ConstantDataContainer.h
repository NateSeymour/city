#ifndef COMPILETIMECONSTANT_H
#define COMPILETIMECONSTANT_H

#include <vector>
#include "Container.h"

namespace city
{
    class ConstantDataContainer : public Container
    {
        std::size_t size_;
        std::size_t offset_;

    public:
        [[nodiscard]] std::size_t GetSize() const noexcept;
        [[nodiscard]] std::size_t GetOffset() const noexcept;

        void LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target) override;

        ConstantDataContainer(std::size_t size, std::size_t offset);
    };
} // namespace city

#endif // COMPILETIMECONSTANT_H
