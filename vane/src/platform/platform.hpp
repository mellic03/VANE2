#pragma once

#include "vane/type.hpp"
#include "vane/iodev.hpp"

#include <SDL3/SDL.h>
#include <cstdint>
#include <unordered_set>

namespace vane
{
    class IoDevice;
    class Platform;
    class PlatformWindow;
}


class vane::Platform
{
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

    template <typename IoDeviceType>
    IoDeviceType *addIoDevice()
    {
        auto *iodev = new IoDeviceType(this);
        mIoDevices.insert(iodev);
        return iodev;
    }
};


struct vane::PlatformWindow
{
    Platform     *mPlatform;
    SDL_Window   *mSdlWin;
    SDL_GLContext mSdlGlCtx;
    SDL_WindowID  mSdlWinID;

    // Should be seperated out
    // --------------------------
    uint32_t mFBO;
    uint32_t mVAO;
    // --------------------------

    PlatformWindow(Platform*, const char *name, int x, int y, int w, int h);
    ~PlatformWindow();
    void update();
    void updateEvent(SDL_Event&);
};


