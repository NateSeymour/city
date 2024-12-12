#ifndef CITY_BUILDER_H
#define CITY_BUILDER_H

#include <type_traits>
#include "Block.h"
#include "Function.h"
#include "value/Value.h"
#include "value/ConstantValue.h"
#include "type/Type.h"

#include "instruction/arithmetic/AddInst.h"
#include "instruction/control/RetInst.h"
#include "instruction/control/BranchInst.h"

namespace city
{
    class Module;

    class Builder
    {
        friend class Module;

        Module &module_;
        Block *insert_point_ = nullptr;

    protected:
        explicit Builder(Module &module);

    public:
        // Blocks
        [[nodiscard]] Block *CreateBlock();

        void SetInsertPoint(Block *block) noexcept;
        void SetInsertPoint(Function *function) noexcept;
        [[nodiscard]] Block *GetInsertPoint() const noexcept;

        // Types
        template<typename T>
        Type GetBuiltinType()
        {
            Type type;

            if constexpr(std::is_integral_v<T>)
            {
                type.size_ = sizeof(T);
                type.native_type_ = NativeType::Integer;
            }
            else if constexpr(std::is_floating_point_v<T>)
            {
                type.size_ = sizeof(T);
                type.native_type_ = NativeType::FloatingPoint;
            }
            else if constexpr(std::is_same_v<T, void>)
            {
                type.size_ = 0;
                type.native_type_ = NativeType::Void;
            }
            else
            {
                static_assert("Unrecognized Native Type!");
            }

            return type;
        }

        // Functions
        [[nodiscard]] Function *CreateFunction(std::string name);
        [[nodiscard]] Function *CreateFunction(std::string name, Type ret);
        [[nodiscard]] Function *CreateFunction(std::string name, Type ret, std::vector<Type> const &args);

        // Values
        template<typename T>
        [[nodiscard]] ConstantValue *CreateConstant(T value)
        {

        }

        // Instructions - Arithmetic
        AddInst *InsertAddInst(Value *lhs, Value *rhs, Value *dst = nullptr);

        // Instructions - Control
        Instruction *CreateLabel();
        BranchInst *InsertBranchInst(Instruction *target);
        RetInst *InsertRetInst(Value *ret);

        // Constructors
        Builder() = delete;
    };
} // city

#endif //CITY_BUILDER_H
