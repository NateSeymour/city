#ifndef CITY_IRBUILDER_H
#define CITY_IRBUILDER_H

#include <cstdlib>
#include <type_traits>
#include "Block.h"
#include "Function.h"
#include "instruction/arithmetic/AddInst.h"
#include "instruction/control/BranchInst.h"
#include "instruction/control/RetInst.h"
#include "instruction/memory/StoreInst.h"
#include "type/Type.h"
#include "value/Value.h"

namespace city
{
    class IRModule;

    class IRBuilder
    {
        friend class IRModule;

        IRModule &module_;
        Block *insert_point_ = nullptr;

    protected:
        template<typename T, typename... Args>
            requires std::derived_from<T, Value>
        [[nodiscard]] T *ReserveLocalValue(Args... args)
        {
            auto &locals = this->insert_point_->local_values_;
            auto &value = locals.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            return dynamic_cast<T *>(value.get());
        }

        template<typename T, typename... Args>
            requires std::derived_from<T, IRInstruction>
        [[nodiscard]] T *ReserveInstruction(Args... args)
        {
            auto &instructions = this->insert_point_->instructions_;
            auto &instruction = instructions.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            return dynamic_cast<T *>(instruction.get());
        }

        explicit IRBuilder(IRModule &module);

    public:
        // Blocks
        [[nodiscard]] Block *CreateBlock();

        void SetInsertPoint(Block *block) noexcept;
        void SetInsertPoint(Function *function) noexcept;
        [[nodiscard]] Block *GetInsertPoint() const noexcept;

        // Types
        template<typename T>
        Type GetType()
        {
            Type type;

            if constexpr (std::is_integral_v<T>)
            {
                type.size_ = sizeof(T);
                type.native_type_ = NativeType::Integer;
            }
            else if constexpr (std::is_floating_point_v<T>)
            {
                type.size_ = sizeof(T);
                type.native_type_ = NativeType::FloatingPoint;
            }
            else if constexpr (std::is_same_v<T, void>)
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
        [[nodiscard]] Value *CreateConstant(Type type, std::vector<std::byte> const &data);

        template<typename T>
        [[nodiscard]] Value *CreateConstant(T value)
        {
            auto type = this->GetType<T>();

            std::vector<std::byte> data(type.size_, static_cast<std::byte>(0));

            memcpy(data.data(), &value, data.size());

            return this->CreateConstant(type, data);
        }

        // Instructions - Arithmetic
        [[nodiscard]] AddInst *InsertAddInst(Value *lhs, Value *rhs);

        // Instructions - Memory
        StoreInst *InsertStoreInst(Value *dst, Value *src);

        // Instructions - Control
        BranchInst *InsertBranchInst(IRInstruction *target);
        RetInst *InsertRetInst(Value *ret);

        // Constructors
        IRBuilder() = delete;
    };
} // namespace city

#endif // CITY_IRBUILDER_H