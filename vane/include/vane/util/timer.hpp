#pragma once

#include <cstdint>


namespace vane
{
    struct MsTimer
    {
    public:
        MsTimer(uint64_t rate, uint64_t startOffset=0);
        bool hasExpired();
        // void reset();

    private:
        const uint64_t mRate;
        uint64_t mCurr, mPrev;
    };


}
