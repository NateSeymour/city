#ifdef __APPLE__
#ifndef CITY_MACOS_H
#define CITY_MACOS_H

#include "ExecutableMemoryHandle.h"

namespace city
{
    int memory_protection_to_native(MemoryProtection protection);
}

#endif //CITY_MACOS_H
#endif //__APPLE__