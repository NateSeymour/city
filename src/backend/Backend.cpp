#include "Backend.h"

using namespace city;

#ifdef __x86_64__

#include "x86/x86.h"

std::unique_ptr<Backend> Backend::CreateHostNative()
{
    return std::make_unique<x86>();
}

#elifdef __aarch64__

#include "aarch64/AArch64.h"

std::unique_ptr<Backend> Backend::CreateHostNative()
{
    return std::make_unique<AArch64>();
}

#endif
