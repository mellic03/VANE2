#pragma once

#include <stdint.h>
#include <stddef.h>

namespace vane::util
{
    template <typename T>
    inline constexpr T align_down( T value, size_t alignment )
    {
        return T(uintptr_t(value) & ~(alignment-1));
    }

    template <typename T>
    inline constexpr T align_up( T value, size_t alignment )
    {
        return T((uintptr_t(value) + alignment-1) & ~(alignment-1));
    }

    template <typename T>
    inline constexpr T *ptr_align( T *ptr, size_t alignment )
    {
        size_t p = reinterpret_cast<size_t>(ptr);
        return reinterpret_cast<T*>((p + alignment - 1) & ~(alignment - 1));
    }

}

