#ifndef COMPILETIMECONSTANT_H
#define COMPILETIMECONSTANT_H

#include "Container.h"

namespace city
{
    class ConstantDataContainer : public Container
    {
        std::size_t size_;
        std::size_t offset_;

    public:
        void Load(IRTranslator &translator, Register &dst) override;
        void Store(IRTranslator &translator, Register &src) override;

        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] std::size_t GetOffset() const noexcept;
        [[nodiscard]] ContainerType GetType() const noexcept override;
        ConstantDataContainer(std::size_t size, std::size_t offset);
        ConstantDataContainer(ConstantDataContainer const &) = delete;
    };
} // namespace city

#endif // COMPILETIMECONSTANT_H
