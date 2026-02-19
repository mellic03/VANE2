#pragma once

#include <atomic> 
#include <cstddef>

namespace vane
{
    namespace detail
    {
        inline static size_t vtid_next_;
    }

    template <typename T>
    inline static size_t vaneTypeID()
    {
        static const size_t id = detail::vtid_next_++;
        return id;
    }

    // class TypeId
    // {
    // private:
    //     static size_t value_;

    // public:
    //     template<typename T>
    //     static size_t next()
    //     { static const size_t id = value_++;  return id; }
    // };

}
