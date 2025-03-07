#ifndef CITY_IRBUILDER_H
#define CITY_IRBUILDER_H

#include <concepts>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include "IRCondition.h"
#include "IRFunction.h"
#include "block/IRBlock.h"
#include "block/IRConditionalBlock.h"
#include "city/container/ConstantDataContainer.h"
#include "city/type/Type.h"
#include "city/value/Value.h"
#include "instruction/arithmetic/AddInst.h"
#include "instruction/arithmetic/DivInst.h"
#include "instruction/arithmetic/MulInst.h"
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
        IRBlock *block_ = nullptr;

    protected:
        [[nodiscard]] Value *ReserveValue(Type type);

        template<typename BinaryInstructionType>
            requires std::derived_from<BinaryInstructionType, IRBinaryInstruction>
        [[nodiscard]] BinaryInstructionType *InsertBinaryInst(Value *lhs, Value *rhs)
        {
            if (this->block_ == nullptr)
            {
                return nullptr;
            }

            auto lhs_type = lhs->GetType();
            auto rhs_type = rhs->GetType();

            if (lhs_type != rhs_type)
            {
                throw std::runtime_error("incompatible types");
            }

            return this->block_->InsertInstruction<BinaryInstructionType>(lhs_type, lhs, rhs);
        }

        explicit IRBuilder(IRModule &module);

    public:
        // Blocks
        IRBlock &InsertBlock();

        void SetInsertPoint(IRBlock &block) noexcept;
        void SetInsertPoint(IRFunction *function) noexcept;
        [[nodiscard]] IRBlock *GetInsertPoint() const;
        [[nodiscard]] IRFunction *GetInsertFunction() const;

        // Functions
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name);
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name, Type ret);
        [[nodiscard]] IRFunction *CreateFunction(std::string const &name, Type ret, std::vector<Type> const &argument_types);

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
        [[nodiscard]] AddInst *InsertAddInst(Value *lhs, Value *rhs)
        {
            return this->InsertBinaryInst<AddInst>(lhs, rhs);
        }

        [[nodiscard]] SubInst *InsertSubInst(Value *lhs, Value *rhs)
        {
            return this->InsertBinaryInst<SubInst>(lhs, rhs);
        }

        [[nodiscard]] MulInst *InsertMulInst(Value *lhs, Value *rhs)
        {
            return this->InsertBinaryInst<MulInst>(lhs, rhs);
        }

        [[nodiscard]] DivInst *InsertDivInst(Value *lhs, Value *rhs)
        {
            return this->InsertBinaryInst<DivInst>(lhs, rhs);
        }

        // Instructions - Control
        [[nodiscard]] CallInst *InsertCallInst(Function *function, std::vector<Value *> const &args = {});
        RetInst *InsertRetInst(Value *retval = nullptr);

        [[nodiscard]] IRConditionalBlock *CreateCondition(Value *lhs, BinaryCondition condition, Value *rhs);

        // Constructors
        IRBuilder() = delete;
    };
} // namespace city

#endif // CITY_IRBUILDER_H
