#pragma once

#include <cstdint>
#include <atomic> 

using vaneid_t = int64_t;

namespace vane
{
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
    inline static vaneid_t vane_typeid_curr_;

    template <typename T>
    struct vane_typeid_impl
    {
        inline static const vaneid_t value = vane::detail::vane_typeid_curr_++;
    };
}

template <typename T>
inline vaneid_t vane_typeid()
{
    static const vaneid_t id = vane::detail::vane_typeid_curr_++;
    return id;
}


// template <typename T>
// constexpr const vaneid_t VaneTypeID = vane::detail::vane_typeid_impl<T>::value;

// template <typename T>
// inline vaneid_t VaneTypeID()
// {
//     using namespace vane::detail;

//     auto curr_id = vane_typeid_curr_;
//     auto next_id = vane_typeid_curr_ + 1;

//     vane_typeid_impl<T>;
    
//     static const vaneid_t id = vane::detail::vane_typeid_curr_++;
//     return id;
// }

// template <typename T>
// inline bool VaneTypeID_exists()
// {

// }

