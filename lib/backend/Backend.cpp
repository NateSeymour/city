#include <city/backend/Backend.h>

using namespace city;

#if defined(__x86_64__) || defined(_WIN64)

#include <city/backend/amd64/Amd64.h>

std::unique_ptr<Backend> Backend::CreateHostNative()
{
    return std::make_unique<Amd64>();
}

#elif defined(__aarch64__)

#include "aarch64/AArch64.h"

std::unique_ptr<Backend> Backend::CreateHostNative()
{
    return std::make_unique<AArch64>();
}

#endif
