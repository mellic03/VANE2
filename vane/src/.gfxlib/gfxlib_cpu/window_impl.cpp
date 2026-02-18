#include "platform_impl.hpp"
#include "vane/log.hpp"

using namespace vane;


gfxlib_cpu::WindowImpl::WindowImpl(Platform *platform, const char *name, int x, int y, int w, int h)
:   mPlatform(platform)
{
    mSdlWin = SDL_CreateWindow(name, 1024, 1024, 0);
    if (mSdlWin == NULL)
    {
        VLOG_FATAL("{}", SDL_GetError());
    }

    mSdlSurf = SDL_GetWindowSurface(mSdlWin);
    if (mSdlSurf == NULL)
    {
        VLOG_FATAL("{}", SDL_GetError());
    }

    mSdlWinID = SDL_GetWindowID(mSdlWin);
    SDL_SetWindowPosition(mSdlWin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    VLOG_INFO("Created window {}", mSdlWinID);
}


gfxlib_cpu::WindowImpl::~WindowImpl()
{
    SDL_DestroyWindow(mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


void gfxlib_cpu::WindowImpl::update()
{
    SDL_UpdateWindowSurface(mSdlWin);
}


void gfxlib_cpu::WindowImpl::updateEvent(SDL_Event &e)
{
    if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        mPlatform->destroyWindow_ptr(this);
    }

    else if (e.type == SDL_EVENT_KEY_UP)
    {
        if (e.key.key == SDLK_ESCAPE)
        {
            mPlatform->destroyWindow_ptr(this);
        }
    }
}
