#pragma once

#include <cstddef>
#include <cstdint>

// using vaneid_t = int64_t;

namespace vane
{
    // static constexpr vaneid_t VANEID_NONE = -1;

    enum class VaneStat: int32_t
    {
        OK = 0,
        ERROR,
        INVALID,
        NO_ACTION
    };

    enum class OpCtrl: uint8_t
    {
        None       = 0,
        Initialize = 1,
        Terminate  = 2
    };

    enum class OpState: uint8_t
    {
        Invalid  = 0,
        Starting,
        Running,
        Stopping,
        Stopped
    };
}



namespace vane::detail
{
    inline static size_t vane_typeid_curr_ = 1;

    template <typename T>
    struct vane_typeid_impl
    {
        inline static const size_t value = vane::detail::vane_typeid_curr_++;
    };
}

// template <typename T>
// constexpr const size_t VaneTypeID = vane::detail::vane_typeid_impl<T>::value;

template <typename T>
inline size_t vane_typeid()
{
    static const size_t id = vane::detail::vane_typeid_curr_++;
    return id;
}

