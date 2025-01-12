#ifndef CITY_X86REGISTER_H
#define CITY_X86REGISTER_H

#include "../../Container.h"
#include "Amd64ModRM.h"

namespace city
{
    class Amd64Builder;

    class Amd64Register : public Container
    {
        friend class Amd64Builder;

    protected:
        Amd64RegisterCode code_;

    public:
        [[nodiscard]] Amd64RegisterCode GetCode() const noexcept;

        Amd64Register(Amd64RegisterCode code);
    };
} // namespace city

#endif // CITY_X86REGISTER_H
