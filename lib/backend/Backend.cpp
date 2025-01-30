#include <city/backend/Backend.h>

using namespace city;

#ifdef __x86_64__

#include <city/backend/amd64/Amd64.h>

std::unique_ptr<Backend> Backend::CreateHostNative()
{
    return std::make_unique<Amd64>();
}

#elifdef __aarch64__

#include "aarch64/AArch64.h"

std::unique_ptr<Backend> Backend::CreateHostNative()
{
    return std::make_unique<AArch64>();
}

#endif
