#pragma once

#include <SDL3/SDL.h>
#include <cstdint>

namespace vane
{
    class PlatformSDL3;
    class WindowSDL3;

    using PlatformType = vane::PlatformSDL3;
    using PlatformEventType = SDL_Event;
}

#include "vane/platform.hpp"


class vane::PlatformSDL3: public vane::iPlatform
{
public:
    PlatformSDL3();
    virtual void pollevents() final;

};


class vane::WindowSDL3: public vane::IoDevice
{
private:
    SDL_Window   *mSdlWin;
    SDL_GLContext mSdlGlCtx;
    SDL_WindowID  mSdlWinID;

    int32_t mGlVersionMajor;
    int32_t mGlVersionMinor;

    // Should be seperated out
    // --------------------------
    uint32_t mFBO;
    uint32_t mVAO;
    // --------------------------

public:
    WindowSDL3(iPlatform*, const char *name, int w, int h);
    virtual ~WindowSDL3();
    virtual void onUpdate() final;
    virtual void onEvent(const PlatformEventType&) final;
};
