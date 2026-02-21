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

    HzTime::HzTime(const MsTime &ms): v_(      1000 / ms.v_  ) {  }
    HzTime::HzTime(const NsTime &ns): v_(1000000000 / ns.v_  ) {  }
    MsTime::MsTime(const HzTime &hz): v_(      1000 / hz.v_  ) {  }
    MsTime::MsTime(const NsTime &ns): v_(     ns.v_ / 1000000) {  }
    NsTime::NsTime(const HzTime &hz): v_(1000000000 / hz.v_  ) {  }
    NsTime::NsTime(const MsTime &ms): v_(   1000000 * ms.v_  ) {  }


    struct PeriodicTimer
    {
    private:
        NsTime mPeriod;
        NsTime mCurr, mPrev;

    public:
        PeriodicTimer(const HzTime &hz): PeriodicTimer(NsTime(hz)) {  }

        PeriodicTimer(const MsTime &ms, const MsTime &offset=0)
        :   mPeriod(ms), mCurr(offset), mPrev(mCurr) {  }

        PeriodicTimer(const NsTime &ns, const NsTime &offset=0)
        :   mPeriod(ns), mCurr(offset), mPrev(mCurr) {  }

        bool hasExpired();
    };

    // inline uint64_t hzToMs(uint64_t ms) { return 1000/ms; }
    // inline uint64_t msToHz(uint64_t hz) { return hz*1000; }

    // inline uint64_t hzToNs(uint64_t ms) { return 1000/ms; }
    // inline uint64_t nsToHz(uint64_t hz) { return hz*1000; }
}







