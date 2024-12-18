#ifndef CITY_OBJECT_H
#define CITY_OBJECT_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "backend/NativeInstruction.h"

namespace city
{
    class Object
    {
        std::vector<std::unique_ptr<NativeInstruction>> instructions_;
        std::unordered_map<std::string, NativeInstruction *> symbol_table_;

    public:
        template<typename InstructionType, typename... Args>
            requires std::derived_from<InstructionType, NativeInstruction>
        NativeInstruction *EmplaceInstruction(Args... args)
        {
            auto &inst = this->instructions_.emplace_back(std::make_unique<InstructionType>(std::forward<Args>(args)...));
            return inst.get();
        }

        void RegisterSymbol(std::string const &name, NativeInstruction *entry);

        [[nodiscard]] std::size_t GetBinarySize() const noexcept;
        std::size_t WriteToBuffer(std::byte *buffer) const;
    };
} // namespace city

#endif // CITY_OBJECT_H
