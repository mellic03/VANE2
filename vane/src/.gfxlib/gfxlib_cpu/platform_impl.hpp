#pragma once

#include <SDL3/SDL.h>


namespace vane
{
    class Platform;

    namespace gfxlib_cpu
    {
        struct WindowImpl
        {
            Platform     *mPlatform;
            SDL_Window   *mSdlWin;
            SDL_Surface  *mSdlSurf;
            SDL_WindowID  mSdlWinID;

            WindowImpl(Platform*, const char *name, int x, int y, int w, int h);
            ~WindowImpl();
            void update();
            void updateEvent(SDL_Event&);
        };
    }
}

namespace vane
{
    using WindowImplType = gfxlib_cpu::WindowImpl;
}


#include "vane/platform.hpp"
#include "vane/iodev.hpp"