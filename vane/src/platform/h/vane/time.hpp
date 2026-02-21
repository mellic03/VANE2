#pragma once

#include <cstdint>

namespace vane::time
{
    struct HzTime;
    struct MsTime;
    struct NsTime;

    struct HzTime
    {
        uint64_t v_;
        HzTime(uint64_t x): v_(x) {  };
        HzTime(const MsTime&);
        HzTime(const NsTime&);
    };

    struct MsTime
    {
        uint64_t v_;
        MsTime(uint64_t x): v_(x) {  };
        MsTime(const HzTime&);
        MsTime(const NsTime&);
    };

    struct NsTime
    {
        uint64_t v_;
        NsTime(uint64_t x): v_(x) {  };
        NsTime(const HzTime&);
        NsTime(const MsTime&);
    };


    struct PeriodicTimer
    {
    private:
        NsTime mPeriod;
        NsTime mCurr, mPrev;

    public:
        PeriodicTimer(const HzTime &hz): PeriodicTimer(NsTime(hz)) {  }

        PeriodicTimer(const MsTime &ms, const MsTime &offset=0)
        :   mPeriod(ms), mCurr(offset), mPrev(offset) {  }

        PeriodicTimer(const NsTime &ns, const NsTime &offset=0)
        :   mPeriod(ns), mCurr(offset), mPrev(offset) {  }

        bool hasExpired();
    };

    // inline uint64_t hzToMs(uint64_t ms) { return 1000/ms; }
    // inline uint64_t msToHz(uint64_t hz) { return hz*1000; }

    // inline uint64_t hzToNs(uint64_t ms) { return 1000/ms; }
    // inline uint64_t nsToHz(uint64_t hz) { return hz*1000; }
}







