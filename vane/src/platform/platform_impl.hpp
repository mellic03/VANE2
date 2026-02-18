#pragma once

#include <SDL3/SDL.h>


namespace vane
{
    class Platform;
}

namespace vane::gfxlib_gl
{
    struct WindowImpl
    {
        Platform     *mPlatform;
        SDL_Window   *mSdlWin;
        SDL_GLContext mSdlGlCtx;
        SDL_WindowID  mSdlWinID;

        WindowImpl(Platform*, const char *name, int x, int y, int w, int h);
        ~WindowImpl();
        void update();
        void updateEvent(SDL_Event&);
    };
}

namespace vane
{
    using WindowImplType = gfxlib_gl::WindowImpl;
}


#include "vane/platform.hpp"
#include "vane/iodev.hpp"
