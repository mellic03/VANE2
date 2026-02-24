#pragma once
#include <cstdint>
#include "vane/assert.hpp"
#include "vane/log.hpp"

namespace vane
{
    class NonCopyable
    {
    public:
        NonCopyable() = default;
        ~NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
        NonCopyable(NonCopyable&&) = default;
        NonCopyable& operator=(NonCopyable&&) = default;
    };

}



namespace vane
{
    template <typename T, uint32_t Capacity>
    class inplace_set;
}



template <typename T, uint32_t Capacity>
class vane::inplace_set: private vane::NonCopyable
{
private:
    T  mBase[Capacity];
    T *mTail;
    const T *mEnd;

public:
    // struct pos_t {
    //     T *p_;
    //     pos_t(T *p): p_(p) {  }
    // };
    // inline static pos_t nopos = pos_t(nullptr);
    using pos_t = T*;
    pos_t nopos = nullptr;

    inplace_set(): mTail(mBase), mEnd(mBase + Capacity) {  }

    pos_t find(const T&);
    pos_t insert(const T&);
    void  erase(const T&);

    T &operator[](int);
    const T &operator[](int) const;

    const int  size()  const { return int(mTail - mBase); }
    const bool empty() const { return (mBase == mTail); }
    const bool full()  const { return (mTail == mEnd); }

};



template <typename T, uint32_t N>
vane::inplace_set<T, N>::pos_t vane::inplace_set<T, N>::find(const T &value)
{
    for (T *p=mBase; p<mTail; p++)
        if (*p == value)
            return pos_t(p);
    return inplace_set::nopos;
}


template <typename T, uint32_t N>
vane::inplace_set<T, N>::pos_t vane::inplace_set<T, N>::insert(const T &v)
{
    if (full()) return inplace_set::nopos;

    T p = find(v);
    if (p != inplace_set::nopos)
        return p;
    
    return new (mTail++) T(v);
}


template <typename T, uint32_t N>
void vane::inplace_set<T, N>::erase(const T &v)
{
    if (T *p = find(v))
    {
        std::swap(*p, *(mTail-1));
        (--mTail)->~T();
    }
}


template <typename T, uint32_t N>
T &vane::inplace_set<T, N>::operator[]( int idx )
{
    VANE_ASSERT((0<=idx && idx<N), "Out of bounds access");
    return mBase[idx];
}


template <typename T, uint32_t N>
const T &vane::inplace_set<T, N>::operator[]( int idx ) const
{
    VANE_ASSERT((0<=idx && idx<N), "Out of bounds access");
    return mBase[idx];
}
