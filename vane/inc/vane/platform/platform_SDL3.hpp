#pragma once

// // #include "./type.hpp"
// #include "./platform/iodev.hpp"

#include <SDL3/SDL.h>
#include <cstdint>
#include <unordered_set>


namespace vane
{
    class Platform;
    class PlatformWindow;

    using PlatformEventType = int;

}



class vane::Platform
{
public:
    class IoDevice
    {
    protected:
        vane::Platform *mPlatform;
    private:
        time::PeriodicTimer mTimer;

    public:
        IoDevice(Platform *p): mPlatform(p), mTimer(time::NsTime(0)) {  }
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

    template <typename T>
    T *addIoDevice()
    {
        static_assert(
            std::is_base_of_v<IoDevice, T>,
            "T must be derivative of vane::Platform::IoDevice"
        );

        auto *ptr = new T(this);
        mIoDevices.insert(static_cast<IoDevice*>(ptr));
        return ptr;
    }
};



class vane::PlatformWindow: public vane::Platform::IoDevice
{
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


// class vane::PlatformWindow
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
