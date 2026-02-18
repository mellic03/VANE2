#pragma once
#include <cstdint>
#include "vane/log.hpp"

namespace vane
{
    template <typename DataType, uint32_t Capacity>
    class inplace_stack;
}


template <typename DataType, uint32_t Capacity>
class vane::inplace_stack
{
private:
    DataType  mData[Capacity];
    int32_t   mTop;
    const int mEnd;

public:
    inplace_stack()
    :   mTop(0), mEnd(int(Capacity)) {  }

    void push(const DataType &value)
    {
        if (mTop < mEnd)
            new (&mData[mTop++]) DataType(value);
        else
            VLOG_WARN("Attempted push onto full stack");
    }

    void pop()
    {
        if (mTop > 0)
            mData[--mTop].~DataType();
        else
            VLOG_WARN("Attempted pop from empty stack");
    }

    DataType &top()
    {
        if (mTop > 0)
            return mData[mTop-1];
        else
            VLOG_WARN("Attempted to read top of empty stack");
    }

    void remove(int idx)
    {
        if (!(0<=idx && idx<Capacity))
        {
            VLOG_WARN("Index out of bounds");
            return;
        }

        std::swap(mData[idx], this->top());
        this->pop();
    }

    DataType &operator[](size_t idx)
    {
        if (0<=idx && idx<Capacity)
            return mData[idx];
        else
            VLOG_WARN("Index out of bounds");
    }

    const DataType &operator[](size_t idx) const
    {
        if (0<=idx && idx<Capacity)
            return mData[idx];
        else
            VLOG_WARN("Index out of bounds");
    }

    const int size()       { return mTop; }
    const int size() const { return mTop; }

    const bool empty()       { return (mTop == 0); }
    const bool empty() const { return (mTop == 0); }

    const bool full()        { return (mTop == mEnd); }
    const bool full()  const { return (mTop == mEnd); }
};
