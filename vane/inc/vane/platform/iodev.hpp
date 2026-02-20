#pragma once

#include <SDL3/SDL_events.h>
#include "vane/time.hpp"

namespace vane
{
    class IoDevice;
    class Platform;
}

class vane::IoDevice
{
public:
    Platform *mPlatform;
    time::PeriodicTimer mTimer;

    IoDevice(Platform *p): mPlatform(p), mTimer(time::MsTime(16)) {  }
    virtual ~IoDevice() {  }

    void base_update()
    {
        if (mTimer.hasExpired())
        {

        }
    }

    virtual void update() = 0;
    virtual void updateEvent(const SDL_Event&) = 0;

protected:
    // inplace_queue<SDL_Event, 16> mEventQueue;

};

