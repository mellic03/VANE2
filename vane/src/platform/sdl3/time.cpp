#include "vane/time.hpp"
#include <SDL3/SDL_timer.h>

using namespace vane::time;

// static uint64_t offset_ = 0;
// PeriodicTimer::PeriodicTimer(const NsTime &ns)
// :   mPeriod(ns), mCurr(offset_), mPrev(offset_)
// {

// }

bool PeriodicTimer::hasExpired()
{
    mCurr = NsTime(SDL_GetTicksNS());
    if (mCurr.v_ > mPrev.v_ + mPeriod.v_)
    {
        mPrev = mCurr;
        return true;
    }
    return false;
}

