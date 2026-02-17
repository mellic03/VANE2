#pragma once
#include <cstdint>

namespace vane
{
    enum class VaneStatus: int32_t
    {
        OK = 0,
        ERROR,
        INVALID
    };
}

