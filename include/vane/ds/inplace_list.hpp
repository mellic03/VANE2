#pragma once
#include <cstdint>

namespace vane
{
    template <typename DataType, uint32_t Capacity>
    class inplace_list;
}


template <typename DataType, uint32_t Capacity>
class vane::inplace_list
{
private:
    DataType mData[Capacity];
    int32_t  mCurr;
    const int mMax;

public:
    inplace_list()
    :   mCurr(0), mMax(int(Capacity)),
    {

    }

    void push(const DataType &x)
    {
        if (mCurr < mMax)
        {
            mData[mCurr++] = x;
        }
    }

    void pop()
    {
        if (mCurr > 0)
        {
            mData[--mCurr].~DataType();
        }
    #ifdef VANE_DEBUG
        else
        {
            // vnlog(vane::LOG_WARN )
        }
    #endif
    }
};
