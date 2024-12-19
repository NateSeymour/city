#ifdef WIN64
#ifndef WINDOWS_H
#define WINDOWS_H

#include <windows.h>
#include "NativeMemoryHandle.h"

namespace city
{
    DWORD memory_protection_to_native(MemoryProtection protection);
}

#endif // WINDOWS_H
#endif
