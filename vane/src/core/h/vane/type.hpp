#pragma once

#include <cstddef>
#include <cstdint>

// using vaneid_t = int64_t;

namespace vane
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        ~NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable &operator=(const NonCopyable&) = delete;
        NonCopyable(NonCopyable&&) = default;
        NonCopyable &operator=(NonCopyable&&) = default;
    };

    class NonMovable
    {
    public:
        NonMovable() = default;
        ~NonMovable() = default;
        NonMovable(const NonMovable&) = default;
        NonMovable &operator=(const NonMovable&) = default;
        NonMovable(NonMovable&&) = delete;
        NonMovable &operator=(NonMovable&&) = delete;
    };

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
    inline static int64_t vane_typeid_curr_ = 1;

    // template <typename T>
    // struct vane_typeid_impl
    // {
    //     inline static const int64_t value = vane::detail::vane_typeid_curr_++;
    // };
}

// template <typename T>
// constexpr const int64_t vane_typeid_v = vane::detail::vane_typeid_impl<T>::value;


template <typename T>
inline int64_t vane_typeid()
{
    static const int64_t id = vane::detail::vane_typeid_curr_++;
    return id;
}




namespace vane
{
    // template <typename T>
    // struct srv_typeid;

    namespace detail
    {
        struct srv_typeid_impl
        {
            inline static int type_idx_ = 0;
        };
    }
}


template <typename T>
inline int srv_typeid()
{
    static const int id = vane::detail::srv_typeid_impl::type_idx_++;
    return id;
}

