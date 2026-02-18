#pragma once
#include "vane/type.hpp"
#include <set>

namespace vane
{
    class IoDevice;

    class Platform
    {
    public:
        Platform();
        bool running();
        void shutdown();
        void update();
        vaneid_t createWindow(const char *name, int w, int h);
        VaneStat destroyWindow(vaneid_t);
        VaneStat destroyWindow_ptr(WindowImplType*);
        WindowImplType *getWindow(vaneid_t);

        template <typename IoDeviceType>
        IoDeviceType *createIoDevice();

    private:
        bool mRunning;
        std::set<WindowImplType*> mWindows;
        std::set<vane::IoDevice*> mIoDevices;

    };
}

template <typename IoDeviceType>
IoDeviceType *vane::Platform::createIoDevice()
{
    auto *iodev = new IoDeviceType(this);
    mIoDevices.insert(iodev);
    return iodev;
}

