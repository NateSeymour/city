#ifndef CITY_INTERFACEMODULE_H
#define CITY_INTERFACEMODULE_H

#include <city/type/Type.h>
#include <string>
#include <vector>
#include "InterfaceFunction.h"

namespace city
{
    class JIT;

    class InterfaceModule
    {
        friend class JIT;
        
    protected:
        std::string name_;
        std::vector<std::unique_ptr<InterfaceFunction>> functions_;

    public:
        template<typename ReturnType, typename... ArgTypes>
        InterfaceFunction *InsertBinding(std::string name, ReturnType (*binding)(ArgTypes...))
        {
            auto return_type = Type::Get<ReturnType>();
            std::vector<Type> arg_types = {Type::Get<ArgTypes>()...};
            void *address = reinterpret_cast<void *>(binding);

            auto &fn = this->functions_.emplace_back(std::make_unique<InterfaceFunction>(std::move(name), return_type, std::move(arg_types), address));

            return fn.get();
        }

        [[nodiscard]] std::string const &GetName() const noexcept;

        InterfaceModule(std::string name) : name_(std::move(name)) {}
    };
} // namespace city

#endif // CITY_INTERFACEMODULE_H
