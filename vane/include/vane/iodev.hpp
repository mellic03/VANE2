#pragma once

#include <SDL3/SDL_events.h>
#include "vane/util/timer.hpp"

namespace vane
{
    class IoDevice;
    class Platform;
}

class vane::IoDevice
{
public:
    Platform *mPlatform;
    MsTimer   mTimer;

    IoDevice(Platform *p, uint64_t hz): mPlatform(p), mTimer(1000/hz) {  }
    virtual ~IoDevice() {  }
    virtual void update() = 0;
    // virtual void updateEvent(const SDL_Event&) = 0;

protected:
    // inplace_queue<SDL_Event, 16> mEventQueue;

};

