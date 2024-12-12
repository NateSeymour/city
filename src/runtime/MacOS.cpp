#ifdef __APPLE__
#include "Runtime.h"
#include <stdexcept>
#include <sys/mman.h>

using namespace city;

void *city::map_exectuable(std::size_t size)
{
    void *addr = mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_JIT, 0, 0);

    if(addr == MAP_FAILED)
    {
        throw std::runtime_error("failed to allocated exectuable memory");
    }

    return addr;
}

void city::unmap_executable(void *addr, std::size_t size)
{
    munmap(addr, size);
}
#endif
