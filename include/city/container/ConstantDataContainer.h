#ifndef COMPILETIMECONSTANT_H
#define COMPILETIMECONSTANT_H

#include <vector>
#include "Container.h"

namespace city
{
    class ConstantDataContainer : public Container
    {
        std::vector<std::byte> data_;

    public:
        [[nodiscard]] std::vector<std::byte> const &GetData() const noexcept;

        void LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target) override;

        ConstantDataContainer(std::vector<std::byte> const &data);
    };
} // namespace city

#endif // COMPILETIMECONSTANT_H
