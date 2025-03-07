#ifndef INTEROP_H
#define INTEROP_H

#if defined(__x86_64__) || defined(_WIN64)

#define CITY_ENABLE_AMD64

#elif defined(__aarch64__)

#define CITY_ENABLE_AARCH64

#endif

#endif // INTEROP_H
