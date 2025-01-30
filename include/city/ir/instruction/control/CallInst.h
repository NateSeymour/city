#ifndef CITY_CALLINST_H
#define CITY_CALLINST_H

#include <city/ir/IRFunction.h>
#include <city/ir/instruction/IRInstruction.h>

namespace city
{
    class CallInst : public IRInstruction
    {
        std::string target_name_;

    public:
        [[nodiscard]] std::string const &GetTargetName() const noexcept;

        void Apply(IRTranslator *interface) override;

        CallInst(Value *return_value, IRFunction *ir_function);
    };
} // namespace city

#endif // CITY_CALLINST_H
