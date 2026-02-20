#pragma once

#include "vane/time.hpp"
#include "vane/type.hpp"

#include <cstdint>
#include <unordered_set>

namespace vane
{
    using PlatformEventType = int;

    class Platform;
    class PlatformWindow;
}


class vane::Platform
{
public:
    class IoDevice
    {
    protected:
        vane::Platform *mPlatform;
    private:
        time::PeriodicTimer timer_;
        vaneid_t typeid_;

    public:
        IoDevice(Platform *p): mPlatform(p), timer_(time::NsTime(0)) {  }
        virtual ~IoDevice() {  }
        virtual void onUpdate() = 0;
        virtual void onEvent(const PlatformEventType&) = 0;
    };

private:
    bool mRunning;
    std::unordered_set<IoDevice*> mIoDevices;
    std::unordered_set<PlatformWindow*> mWindows;

public:
    Platform();

    bool running();
    void shutdown();
    void update();

    vaneid_t createWindow(const char *name, int w, int h);
    VaneStat destroyWindow(vaneid_t);
    VaneStat destroyWindow_ptr(PlatformWindow*);
    PlatformWindow *getWindow(vaneid_t);

    template <typename T, typename... Args>
    T *iodev_create(Args... args);

    template <typename T>
    T *iodev_get();
};



template <typename T, typename... Args>
T *vane::Platform::iodev_create(Args... args)
{
    IoDevice *iodev;

    static_assert(
        std::is_base_of_v<IoDevice, T>,
        "T must be derivative of vane::Platform::IoDevice"
    );

    iodev = static_cast<IoDevice*>(new T(this, args...));
    iodev->typeid_ = vane_typeid<T>;
    mIoDevices.insert(iodev);

    return iodev;
}


template <typename T>
T *vane::Platform::iodev_get()
{
    static_assert(
        std::is_base_of_v<IoDevice, T>,
        "T must be derivative of vane::Platform::IoDevice"
    );

    for (auto *iodev: mIoDevices)
    {
    }

}



// struct vane::PlatformWindow
// {
//     Platform     *mPlatform;
//     SDL_Window   *mSdlWin;
//     SDL_GLContext mSdlGlCtx;
//     SDL_WindowID  mSdlWinID;

//     // Should be seperated out
//     // --------------------------
//     uint32_t mFBO;
//     uint32_t mVAO;
//     // --------------------------

//     PlatformWindow(Platform*, const char *name, int x, int y, int w, int h);
//     ~PlatformWindow();
//     void update();
//     void updateEvent(SDL_Event&);
// };

