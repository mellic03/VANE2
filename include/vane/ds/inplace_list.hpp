#pragma once
#include <cstdint>
#include "vane/log.hpp"

namespace vane
{
    template <typename DataType, uint32_t Capacity>
    class inplace_list;
}


template <typename DataType, uint32_t Capacity>
class vane::inplace_list
{
private:
    DataType  mData[Capacity];
    int32_t   mTop;
    const int mEnd;

public:
    inplace_list()
    :   mTop(0), mEnd(int(Capacity))
    {
        
    }

    void push_back(const DataType &value)
    {
    #ifdef VANE_DEBUG
        if (!(mTop < mEnd))
        {
            vnlog(LogType::ERROR, "vane::inplace_list<DataType, %u>::push_back: Buffer Overflow!\n");
            return;
        }
    #endif
        new (&mData[mTop++]) DataType(value);
    }

    void pop_back()
    {
    #ifdef VANE_DEBUG
        if (!(0 < mTop))
        {
            vnlog(LogType::ERROR, "vane::inplace_list<DataType, %u>::pop_back: Buffer Underflow!\n");
            return;
        }
    #endif
        mData[--mTop]->~DataType(); // manual destructor
    }

    DataType &back()
    {
    #ifdef VANE_DEBUG
        if (!(mTop == 0))
        {
            vnlog(LogType::ERROR, "vane::inplace_list<DataType, %u>::back: Invalid Reference!\n");
        }
    #endif
        return mData[mTop-1];
    }


    DataType &operator[]( int idx )
    {
    #ifdef VANE_DEBUG
        if (!(0<=idx && idx<mCap))
        {
            vnlog(LogType::ERROR, "vane::inplace_list<DataType, %u>::operator[]: Invalid Index!\n");
        }
    #endif
        return mData[idx];
    }

    const DataType &operator[]( int idx ) const
    {
    #ifdef VANE_DEBUG
        if (!(0<=idx && idx<mCap))
        {
            vnlog(LogType::ERROR, "vane::inplace_list<DataType, %u>::operator[]: Invalid Index!\n");
        }
    #endif
        return mData[idx];
    }

    const int size()       { return mTop; }
    const int size() const { return mTop; }
};
