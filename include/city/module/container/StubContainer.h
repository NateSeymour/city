#ifndef STUBCONTAINER_H
#define STUBCONTAINER_H

#include <string>
#include "Container.h"

namespace city
{
    class StubContainer : public Container
    {
    public:
        [[nodiscard]] std::size_t GetSize() const noexcept override;
        [[nodiscard]] ContainerType GetType() const noexcept override;

        void Load(IRTranslator &translator, Register &dst) override;
        void Store(IRTranslator &translator, Register &src) override;
    };
} // namespace city

#endif // STUBCONTAINER_H
