#pragma once

#include <cstddef>
#include <cstdint>

namespace vane
{
    struct ThreadMemoryRegion;
    ThreadMemoryRegion const *createThreadMemory(size_t size);
}


