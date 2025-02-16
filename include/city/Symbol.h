#ifndef CITY_SYMBOL_H
#define CITY_SYMBOL_H

#include <string>
#include <unordered_map>
#include "Function.h"

namespace city
{
    class Symbol : public Function
    {
    protected:
        void *location_ = nullptr;

    public:
        [[nodiscard]] void *GetLocation() const noexcept
        {
            return this->location_;
        }

        void SetLocation(void *location) noexcept
        {
            this->location_ = location;
        }

        template<typename ReturnType, typename... Args>
        auto ToPointer()
        {
            return reinterpret_cast<ReturnType (*)(Args...)>(this->location_);
        }

        Symbol(Function const &function, void *location) : Function(function), location_(location) {}
    };

    using SymbolTable = std::unordered_map<std::string, Symbol>;
} // namespace city

#endif // CITY_SYMBOL_H
