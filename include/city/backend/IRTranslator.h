#ifndef IRTRANSLATOR_H
#define IRTRANSLATOR_H

#include <memory>
#include <span>
#include <vector>

#include "NativeModule.h"
#include "city/container/ConstantDataContainer.h"
#include "city/container/Register.h"
#include "city/container/StackAllocationContainer.h"
#include "city/container/StubContainer.h"
#include "city/ir/IRFunction.h"

#include "city/ir/instruction/arithmetic/AddInst.h"
#include "city/ir/instruction/arithmetic/DivInst.h"
#include "city/ir/instruction/arithmetic/MulInst.h"
#include "city/ir/instruction/arithmetic/SubInst.h"
#include "city/ir/instruction/control/CallInst.h"
#include "city/ir/instruction/control/RetInst.h"

namespace city
{
    class IRTranslator
    {
    protected:
        NativeModule &module_;
        IRFunction &ir_function_;

        std::int64_t stack_depth_ = 0;
        std::vector<std::unique_ptr<StackAllocationContainer>> stack_;

        Value stub_base_pointer_{Type::Get<void *>()};

        std::uint64_t register_dislocation_count_ = 0;

        void AlignStack(unsigned int alignment) noexcept;

        [[nodiscard]] StackAllocationContainer &AcquireStackSpace(Type type);
        void PersistRegisterBank(std::span<Register *> bank);
        void PersistScratchRegisters();

        [[nodiscard]] virtual std::span<Register *> GetScratchRegisterBank(NativeType type) = 0;

        /**
         * Returns a reference to an empty, unlocked register.
         * @param type
         * @return
         */
        [[nodiscard]] Register &AcquireScratchRegister(NativeType type);

        /**
         * Move the value out of a register if it has one and returns it.
         * @param reg
         * @return
         */
        [[nodiscard]] Register &AcquireScratchRegister(Register &reg);

        /**
         * Loads a value into a scratch register and returns guard. Will not copy the value if it is already register-bound.
         * If the value is non-constant, its ownership will be transferred to the new register. If this is not desired, use IRTranslator::CopyValueR.
         * @param value Value to load into a scratch register. Ownership is transferred.
         * @return Register guard
         */
        [[nodiscard]] Register &LoadValueR(Value &value);

        /**
         * Loads a value into a specific register. Will bump that register value into the stack if it isn't locked, otherwise will throw.
         * @param dst
         * @param value
         * @return
         */
        [[nodiscard]] Register &LoadValueR(Register &dst, Value &value);

        /**
         * Copies value into a scratch register and returns guard. If value is already register-bound, will be copied into new register.
         * Optimal for destructive operations.
         * @param value Value to copy into register. Ownership is not transferred.
         * @return
         */
        [[nodiscard]] Register &CopyValueR(Value &value);

        /**
         * Copies value into a specific scratch register and returns guard. Will throw if value is already in that register.
         * Optimal for destructive operations.
         * @param value Value to copy into register. Ownership is not transferred.
         * @return
         */
        [[nodiscard]] Register &CopyValueR(Register &dst, Value &value);

        /**
         * Move value into container. If value is not register-bound, a tmp register is used to facilitate the movement.
         * @param dst Destination container
         * @param value Value to be moved. Ownership is transferred.
         */
        void MoveValue(Container &dst, Value &value);

        [[nodiscard]] std::size_t GetStubIndex(std::string const &name) const;

    public:
        virtual void TranslateInstruction(AddInst &inst) = 0;
        virtual void TranslateInstruction(DivInst &inst) = 0;
        virtual void TranslateInstruction(MulInst &inst) = 0;
        virtual void TranslateInstruction(SubInst &inst) = 0;
        virtual void TranslateInstruction(CallInst &inst) = 0;
        virtual void TranslateInstruction(RetInst &inst) = 0;

        virtual void Load(Register &dst, ConstantDataContainer &src) = 0;
        virtual void Load(Register &dst, StackAllocationContainer &src) = 0;
        virtual void Load(Register &dst, StubContainer &src) = 0;
        virtual void Load(Register &dst, Register &src) = 0;

        virtual void Store(StackAllocationContainer &dst, Register &src) = 0;
        virtual void Store(Register &dst, Register &src) = 0;

        IRTranslator(NativeModule &module, IRFunction &ir_function);
        virtual ~IRTranslator() = default;
    };
} // namespace city

#endif // IRTRANSLATOR_H
