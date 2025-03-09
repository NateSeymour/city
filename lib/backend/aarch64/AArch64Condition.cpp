#include "city/backend/aarch64/AArch64Condition.h"

using namespace city;

std::map<BinaryCondition, AArch64Condition> const city::aarch64_condition_translation_map = {
        {BinaryCondition::EqualTo, AArch64Condition::EQ},

        {BinaryCondition::GreaterThan, AArch64Condition::GT},
        {BinaryCondition::LessThan, AArch64Condition::LT},

        {BinaryCondition::GreaterOrEqualTo, AArch64Condition::GE},
        {BinaryCondition::LessOrEqualTo, AArch64Condition::LE},
};

AArch64Condition city::aarch64_negate_condition(AArch64Condition condition)
{
    // Bit zero of the condition is the negation bit.
    auto negated_condition = static_cast<std::uint8_t>(condition) ^ (0b0001);

    return static_cast<AArch64Condition>(negated_condition);
}
