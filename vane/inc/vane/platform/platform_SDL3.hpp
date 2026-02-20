#pragma once

#include <SDL3/SDL.h>
#include <cstdint>
#include <unordered_set>

namespace vane
{
    using PlatformEventType = SDL_Event;
}

#include "../platform.hpp"




vane::OpState PlatformSDL3_init();
bool PlatformSDL3_poll(vane::Platform&, vane::PlatformEventType*);

namespace vane
{
    class PlatformWindow: public Platform::IoDevice
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
        PlatformWindow(Platform*, const char *name, int w, int h);
        virtual ~PlatformWindow();
        virtual void onUpdate() final;
        virtual void onEvent(const PlatformEventType&) final;
    };
}
