#include "vane/util/timer.hpp"
#include <SDL3/SDL_timer.h>


vane::MsTimer::MsTimer(uint64_t rate, uint64_t startOffset)
:   mRate(rate), mCurr(startOffset), mPrev(startOffset)
{

}


bool vane::MsTimer::hasExpired()
{
    mCurr = SDL_GetTicks();
    if (mCurr > mPrev + mRate)
    {
        mPrev = mCurr;
        return true;
    }
    return false;
}

