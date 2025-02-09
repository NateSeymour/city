#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <city/backend/IRTranslator.h>
#include <city/container/StackAllocationContainer.h>
#include "Amd64Function.h"
#include "Amd64Module.h"
#include "container/Amd64RegisterBank.h"

namespace city
{
    enum class ConflictStrategy
    {
        Save,
        Discard,
    };

    enum class LoadType
    {
        Value,
        Pointer,
        Optimal,
    };

    class Amd64FunctionTranslator : IRTranslator
    {
        friend class ConstantDataContainer;
        friend class StackAllocationContainer;
        friend class Amd64Register;

        std::uint64_t register_dislocation_count_ = 0;

    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;

        template<typename IRInstructionType, typename NativeInstructionType>
            requires requires(NativeInstructionType) {
                NativeInstructionType::MR64;
                NativeInstructionType::SDA;
            }
        void TranslateBinaryInstruction(IRInstructionType &inst)
        {
            auto &dsttmp = this->CopyValue(*inst.GetLHS());
            auto &srctmp = this->CopyValue(*inst.GetRHS());

            Type optype = inst.GetLHS()->GetType();
            if (optype.GetNativeType() == NativeType::Integer)
            {
                this->Insert(NativeInstructionType::MR64(dsttmp, srctmp));
            }
            else
            {
                this->Insert(NativeInstructionType::SDA(dsttmp, srctmp));
            }

            srctmp.Disassociate();
            dsttmp.Disassociate();
            this->Associate(inst, dsttmp);

            inst.GetLHS()->DecrementReadCount();
            inst.GetRHS()->DecrementReadCount();
        }

        void Load(Amd64Register &dst, ConstantDataContainer &src);
        void Load(Amd64Register &dst, StackAllocationContainer &src);
        void Load(Amd64Register &dst, Amd64Register &src);

        void Store(StackAllocationContainer &dst, Amd64Register &src);
        void Store(Amd64Register &dst, Amd64Register &src);

        [[nodiscard]] Amd64Register &CopyValue(Value &value);

        void MoveValue(StackAllocationContainer &dst, Amd64Register &src);
        void MoveValue(Amd64Register &dst, Amd64Register &src, ConflictStrategy strategy);
        void MoveValue(Amd64Register &dst, Value &value, ConflictStrategy strategy);

        void HandleConflict(Amd64Register &reg, ConflictStrategy strategy);

        [[nodiscard]] StackAllocationContainer &AcquireStackSpace(std::size_t size);
        [[nodiscard]] Amd64Register &AcquireGPRegister(Amd64RegisterValueType value_type = Amd64RegisterValueType::Integer);

        void Associate(Value &value, Container &container);

        void Insert(Amd64Instruction &&inst);
        void InsertProlog(Amd64Instruction &&inst);

    public:
        Amd64Module &module;
        Amd64Function function;
        IRFunction &ir_function;
        Amd64RegisterBank registers;
        std::int64_t stack_depth = 0;
        std::vector<std::unique_ptr<StackAllocationContainer>> local_swap_;

        [[nodiscard]] Amd64Function Translate();

        explicit Amd64FunctionTranslator(Amd64Module &module, IRFunction &ir_function);
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
