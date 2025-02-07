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
        void Load(Amd64FunctionTranslator &translator, Amd64Register &dst) override;
        void Store(Amd64FunctionTranslator &translator, Amd64Register &src) override;

        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] std::size_t GetOffset() const noexcept;

        ConstantDataContainer(std::size_t size, std::size_t offset);
    };
} // namespace city

#endif // COMPILETIMECONSTANT_H
