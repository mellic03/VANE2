#pragma once

#include <cstdint>
#include <atomic> 


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



namespace vane::detail
{
    inline static vane::vaneid_t vtid_next_;
}


template <typename T>
inline static vane::vaneid_t vane_typeid()
{
    static const vane::vaneid_t id = vane::detail::vtid_next_++;
    return id;
}
