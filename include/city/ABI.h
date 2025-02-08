/**
 * @file Defines macros for determining system ABI. Important in determining register roles and argument passing.
 */
#ifndef CITY_ABI_H
#define CITY_ABI_H

#if defined(__APPLE__)
#define ABI_SYSV
#elif defined(WIN64) || defined(_WIN64)
#define ABI_WINDOWS
#endif

#endif // CITY_ABI_H
