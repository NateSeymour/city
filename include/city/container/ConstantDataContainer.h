#ifndef COMPILETIMECONSTANT_H
#define COMPILETIMECONSTANT_H

#include <cstdint>
#include <vector>
#include "Container.h"

namespace city
{
    class ConstantDataContainer : public Container
    {
        std::vector<std::uint8_t> data_;

    public:
        void Load(IRTranslator &translator, Register &dst) override;
        void Store(IRTranslator &translator, Register &src) override;

        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] ContainerType GetType() const noexcept override;
        [[nodiscard]] std::vector<std::uint8_t> const &GetDataBuffer() const noexcept;

        ConstantDataContainer(std::vector<std::uint8_t> data);
    };
} // namespace city

#endif // COMPILETIMECONSTANT_H
