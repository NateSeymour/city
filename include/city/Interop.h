#ifndef INTEROP_H
#define INTEROP_H

#include <city/archc/AArch64.h>
#include <city/archc/Amd64.h>

namespace city
{
#if defined(__x86_64__) || defined(_WIN64)
    using NativeArchitecture = Amd64;
#elif defined(__aarch64__)
    using NativeArchitecture = AArch64;
#endif
}

#endif // INTEROP_H
