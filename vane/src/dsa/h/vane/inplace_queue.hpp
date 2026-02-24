#pragma once

#include "vane/log.hpp"
#include "vane/type.hpp"


namespace vane
{
    template <typename DataType, uint32_t Capacity>
    class inplace_queue;
}


template <typename DataType, uint32_t Capacity>
class vane::inplace_queue: private vane::NonCopyable
{
private:
    DataType mData[Capacity];
    int32_t  mSize, mRdIdx, mWtIdx;

public:
    inplace_queue()
    :   mSize(0), mRdIdx(0), mWtIdx(0)
    {
        
    }

    void push(const DataType &value)
    {
        if (mSize < Capacity)
        {
            new (&mData[mWtIdx]) DataType(value);
            mWtIdx = (mWtIdx+1) % Capacity;
            mSize += 1;
        }
    }

    void pop()
    {
        if (mSize > 0)
        {
            mData[mRdIdx].~DataType();
            mRdIdx = (mRdIdx+1) % Capacity;
            mSize -= 1;
        }
    }

    DataType &front()
    {
    #ifdef VANE_DEBUG
        if (mSize == 0)
            VLOG_ERROR("Attempted to read front of empty queue");
    #endif
        return mData[mRdIdx];
    }

    DataType &back()
    {
    #ifdef VANE_DEBUG
        if (mSize == 0)
            VLOG_ERROR("Attempted to read back of empty queue");
    #endif
        return mData[mWtIdx-1];
    }

    const int size()       { return mSize; }
    const int size() const { return mSize; }

    const bool empty()       { return (mSize == 0); }
    const bool empty() const { return (mSize == 0); }

    const bool full()        { return (mSize == Capacity); }
    const bool full()  const { return (mSize == Capacity); }

};
