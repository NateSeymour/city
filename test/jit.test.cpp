#include "jit.test.h"
#include <cmath>

extern "C" double jitstd_pow(double a, double b)
{
    return std::pow(a, b);
}
