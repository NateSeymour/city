#ifndef CITY_IRBUILDER_H
#define CITY_IRBUILDER_H

#include <city/Value.h>
#include <city/container/ConstantDataContainer.h>
#include <city/type/Type.h>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include "IRFunction.h"
#include "block/IRBlock.h"
#include "instruction/arithmetic/AddInst.h"
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

        template<typename BinaryInstructionType>
            requires std::derived_from<BinaryInstructionType, IRBinaryInstruction>
        [[nodiscard]] Value *InsertBinaryInst(Value *lhs, Value *rhs)
        {
            auto lhs_type = lhs->GetType();
            auto rhs_type = rhs->GetType();

            if (lhs_type != rhs_type)
            {
                throw std::runtime_error("incompatible types");
            }

            auto retval = this->ReserveLocalValue(lhs_type);
            (void)this->ReserveInstruction<BinaryInstructionType>(retval, lhs, rhs);

            return retval;
        }

        explicit IRBuilder(IRModule &module);

    public:
        // Blocks
        [[nodiscard]] IRBlock &CreateBlock();

        void SetInsertPoint(IRBlock &block) noexcept;
        void SetInsertPoint(IRFunction *function) noexcept;
        [[nodiscard]] IRBlock &GetInsertPoint() const;
        [[nodiscard]] IRFunction *GetInsertFunction() const;

        // Functions
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name);
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name, Type ret);
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name, Type ret, std::vector<Type> const &args);

        // Values
        [[nodiscard]] Value *CreateConstant(Type type, std::vector<std::uint8_t> const &data);

        template<typename T>
        [[nodiscard]] Value *CreateConstant(T value)
        {
            auto type = Type::Get<T>();

            std::vector<std::uint8_t> data(type.size_, 0);

            std::memcpy(data.data(), &value, data.size());

            return this->CreateConstant(type, data);
        }

        // Instructions - Arithmetic
        [[nodiscard]] Value *InsertAddInst(Value *lhs, Value *rhs)
        {
            return this->InsertBinaryInst<AddInst>(lhs, rhs);
        }

        [[nodiscard]] Value *InsertSubInst(Value *lhs, Value *rhs)
        {
            return this->InsertBinaryInst<SubInst>(lhs, rhs);
        }

        // Instructions - Control
        [[nodiscard]] Value *InsertCallInst(IRFunction *function);
        Value *InsertRetInst(Value *retval = nullptr);

        // Constructors
        IRBuilder() = delete;
    };
} // namespace city

#endif // CITY_IRBUILDER_H
