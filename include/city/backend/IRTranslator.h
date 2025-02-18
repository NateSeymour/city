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
    struct BinaryOperation
    {
        IRBinaryInstruction &inst;
        Register &dst;
        Register &src1;
        Register &src2;
        std::size_t opsize;
        NativeType optype;

        void Persist() const
        {
            dst.ClearTempValue();
            src1.ClearTempValue();
            src2.ClearTempValue();

            this->inst.GetLHS()->DecrementReadCount();
            this->inst.GetRHS()->DecrementReadCount();

            dst.InstantiateValue(&inst);
        }
    };

    class IRTranslator
    {
    protected:
        NativeModule &module_;
        IRFunction &ir_function_;

        std::int64_t stack_depth_ = 0;
        std::vector<std::unique_ptr<StackAllocationContainer>> stack_;

        std::uint64_t register_dislocation_count_ = 0;

        void AlignStack(unsigned int alignment) noexcept;

        [[nodiscard]] StackAllocationContainer &AcquireStackSpace(Type type);
        void PersistRegisterBank(std::span<Register *> bank);
        void PersistScratchRegisters();

        [[nodiscard]] virtual std::span<Register *> GetScratchRegisterBank(NativeType type) = 0;

        [[nodiscard]] Register &AcquireScratchRegister(NativeType type);

        /**
         *
         * @param inst Instruction to prepare
         * @param destructive The instruction is destructive, meaning that it overwrites its first source argument. In this case, `dst` and `src1` will be aliases. `src1` will be a
         * strict copy of the original value.
         * @return
         */
        [[nodiscard]] BinaryOperation PrepareBinaryOperation(IRBinaryInstruction &inst, bool destructive = false);

        /**
         * Loads a value into a scratch register. Default behavior is to do nothing if the value is already in a register.
         * @param value Value to load into a scratch register
         * @param copy
         * @return
         */
        [[nodiscard]] Register &LoadValue(Value &value, bool copy = false);

        [[nodiscard]] std::size_t GetStubIndex(std::string const &name) const;

        void MoveValue(Container &dst, Value &value);

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
