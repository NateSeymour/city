#ifndef CITY_IRBUILDER_H
#define CITY_IRBUILDER_H

#include <city/Value.h>
#include <city/container/ConstantDataContainer.h>
#include <city/type/Type.h>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include "IRFunction.h"
#include "block/IRBlock.h"
#include "instruction/arithmetic/AddInst.h"
#include "instruction/arithmetic/FAddInst.h"
#include "instruction/arithmetic/SubInst.h"
#include "instruction/control/CallInst.h"
#include "instruction/control/RetInst.h"

namespace city
{
    class IRModule;

    class IRBuilder
    {
        friend class IRModule;

        IRModule &module_;
        IRBlock *insert_point_ = nullptr;

    protected:
        [[nodiscard]] ConstantDataContainer *CreateConstantDataContainer(std::size_t size, std::size_t offset);

        [[nodiscard]] Value *ReserveLocalValue(Type type);

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
        [[nodiscard]] IRBlock &CreateBlock();

        void SetInsertPoint(IRBlock &block) noexcept;
        void SetInsertPoint(IRFunction *function) noexcept;
        [[nodiscard]] IRBlock &GetInsertPoint() const;

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
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name);
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name, Type ret);
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name, Type ret, std::vector<Type> const &args);

        // Values
        [[nodiscard]] Value *CreateConstant(Type type, std::vector<std::uint8_t> const &data);

        template<typename T>
        [[nodiscard]] Value *CreateConstant(T value)
        {
            auto type = this->GetType<T>();

            std::vector<std::uint8_t> data(type.size_, 0);

            std::memcpy(reinterpret_cast<void *>(data.data()), reinterpret_cast<void *>(&value), data.size());

            return this->CreateConstant(type, data);
        }

        // Instructions - Arithmetic
        [[nodiscard]] AddInst *InsertAddInst(Value *lhs, Value *rhs);
        [[nodiscard]] SubInst *InsertSubInst(Value *lhs, Value *rhs);

        // Instructions - Arithmetic (Floating Point)
        [[nodiscard]] FAddInst *InsertFAddInst(Value *lhs, Value *rhs);

        // Instructions - Control
        CallInst *InsertCallInst(IRFunction *function);
        RetInst *InsertRetInst(Value *return_value = nullptr);

        // Constructors
        IRBuilder() = delete;
    };
} // namespace city

#endif // CITY_IRBUILDER_H
