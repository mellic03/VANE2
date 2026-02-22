#include <vane.hpp>

using namespace vane::time;

HzTime::HzTime(const MsTime &ms): v_(      1000 / ms.v_  ) {  }
HzTime::HzTime(const NsTime &ns): v_(1000000000 / ns.v_  ) {  }
MsTime::MsTime(const HzTime &hz): v_(      1000 / hz.v_  ) {  }
MsTime::MsTime(const NsTime &ns): v_(     ns.v_ / 1000000) {  }
NsTime::NsTime(const HzTime &hz): v_(1000000000 / hz.v_  ) {  }
NsTime::NsTime(const MsTime &ms): v_(   1000000 * ms.v_  ) {  }


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

