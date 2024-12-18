#ifndef CITY_OBJECT_H
#define CITY_OBJECT_H

#include <memory>
#include <vector>
#include "backend/NativeInstruction.h"

namespace city
{
    class Object
    {
        std::vector<std::unique_ptr<NativeInstruction>> instructions_;

    public:
        template<typename InstructionType, typename... Args>
            requires std::derived_from<InstructionType, NativeInstruction>
        NativeInstruction *EmplaceInstruction(Args... args)
        {
            auto &inst = this->instructions_.emplace_back(std::make_unique<InstructionType>(std::forward<Args>(args)...));
            return inst.get();
        }
    };
} // namespace city

#endif // CITY_OBJECT_H
