#pragma once
#include <cstdint>

namespace vane
{
    using vaneid_t = int32_t;

    static constexpr vaneid_t VANEID_NONE = -1;

    enum class VaneStat: int32_t
    {
        OK = 0,
        ERROR,
        INVALID
    };
}

