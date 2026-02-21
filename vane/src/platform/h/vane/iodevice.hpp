#pragma once

#include "time.hpp"
#include "vane/type.hpp"


namespace vane
{
    class IoDevice;
    class Window;
    class Platform;
}


class vane::IoDevice
{
protected:
    vane::Platform *mPlatform;

private:
    friend class vane::Platform;
    time::PeriodicTimer timer_;
    size_t typeid_;
    bool   kill_;

public:
    IoDevice(Platform *p): mPlatform(p), timer_(time::NsTime(0)) {  }
    virtual ~IoDevice() {  }
    virtual void onUpdate() = 0;
    virtual void onEvent(void*) = 0;
};

