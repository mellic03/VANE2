#include "platform_SDL3.hpp"
#include "vane/vanelog.hpp"
#include <SDL3/SDL.h>


struct WindowImpl
{
    static constexpr size_t MAX_WINDOWS = 8;
    static inline int32_t numWindows_ = 0;

    SDL_Window *sdlWin;
    SDL_Surface *sdlSurf;
    SDL_WindowID sdlWinID;

    WindowImpl(): sdlWin(nullptr), sdlSurf(nullptr), sdlWinID(0) {  }

    bool isInUse() { return (bool)sdlWin; }
    bool notInUse() { return !isInUse(); }

    void init(SDL_Window *win, SDL_Surface *surf)
    {
        sdlWin = win;
        sdlSurf = surf;
        sdlWinID = SDL_GetWindowID(win);
        numWindows_ += 1;
    }

    void deinit()
    {
        sdlWin = nullptr;
        sdlSurf = nullptr;
        sdlWinID = 0;
        numWindows_ -= 1;
    }
};

static WindowImpl windows_[WindowImpl::MAX_WINDOWS];

static vane::vaneid_t WindowImpl_alloc(SDL_Window*, SDL_Surface*);
// static vane::VaneStat WindowImpl_free(SDL_WindowID);




vane::PlatformSDL3::PlatformSDL3()
:   mRunning(true)
{
    if (false == SDL_Init(SDL_INIT_VIDEO))
    {
        VLOG_ERROR("{}", SDL_GetError());
        exit(1);
    }

    VLOG_INFO("SDL3 Initialized");
}

bool vane::PlatformSDL3::running()
{
    return mRunning;
}

void vane::PlatformSDL3::shutdown()
{
    VLOG_INFO("Shutdown initiated");

    WindowImpl *winDesc = &(windows_[0]);
    for (int i=0; i<WindowImpl::MAX_WINDOWS; i++)
    {
        if (winDesc->isInUse())
            destroyWindow(winDesc->sdlWinID);
        winDesc++;
    }
    SDL_Quit();
    mRunning = false;

    VLOG_INFO("Shutdown complete");
}



void vane::PlatformSDL3::update()
{
    if (WindowImpl::numWindows_ == 0)
    {
        this->shutdown();
        return;
    }

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        SDL_Window *eWin = SDL_GetWindowFromEvent(&e);

        if (e.type == SDL_EVENT_QUIT)
        {
            if (eWin) destroyWindow(e.window.windowID);
            else      this->shutdown();
        }

        else if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        {
            destroyWindow(e.window.windowID);
        }

        else if (e.type == SDL_EVENT_KEY_UP)
        {
            if (e.key.key == SDLK_ESCAPE)
            {
                destroyWindow(e.window.windowID);
            }
        }
    }

    for (int i=0; i<WindowImpl::MAX_WINDOWS; i++)
    {
        auto &win = windows_[i];
        if (win.sdlWin)
        {
            SDL_UpdateWindowSurface(win.sdlWin);
        }
    }
}


vane::vaneid_t vane::PlatformSDL3::createWindow(const char *name, int w, int h)
{
    if (WindowImpl::numWindows_ == WindowImpl::MAX_WINDOWS)
    {
        return VANEID_NONE;
    }

    SDL_Window *sdlWin = SDL_CreateWindow(name, 1024, 1024, 0);
    if (sdlWin == nullptr)
    {
        VLOG_ERROR("{}", SDL_GetError());
        return VANEID_NONE;
    }

    SDL_Surface *sdlSurf = SDL_GetWindowSurface(sdlWin);
    if (sdlSurf == nullptr)
    {
        VLOG_ERROR("{}", SDL_GetError());
        SDL_DestroyWindow(sdlWin);
        return VANEID_NONE;
    }

    SDL_SetWindowPosition(sdlWin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    vaneid_t sdlWinId = WindowImpl_alloc(sdlWin, sdlSurf);
    VLOG_INFO("Created window {}", sdlWinId);

    return sdlWinId;
}


vane::VaneStat vane::PlatformSDL3::destroyWindow(vane::vaneid_t sdlWinId)
{
    WindowImpl *desc = &(windows_[0]);
    for (int i=0; i<WindowImpl::MAX_WINDOWS; i++)
    {
        if (desc->isInUse() && desc->sdlWinID == sdlWinId)
        {
            SDL_DestroyWindow(desc->sdlWin);
            desc->deinit();
            VLOG_INFO("Destroyed window {}", sdlWinId);
            return VaneStat::OK;
        }
        desc++;
    }

    VLOG_ERROR("Invalid WindowID {}", (uint32_t)sdlWinId);

    return VaneStat::INVALID;
}






static vane::vaneid_t WindowImpl_alloc(SDL_Window *sdlWin, SDL_Surface *sdlSurf)
{
    using namespace vane;

    WindowImpl *desc = &(windows_[0]);
    for (size_t i=0; i<WindowImpl::MAX_WINDOWS; i++)
    {
        if (desc->notInUse())
        {
            desc->init(sdlWin, sdlSurf);
            return vaneid_t(desc->sdlWinID);
        }
        desc++;
    }

    return VANEID_NONE;
}


// static vane::VaneStat WindowImpl_free(SDL_WindowID sdlWinId)
// {
//     using namespace vane;

//     for (int i=0; i<WindowImpl::MAX_WINDOWS; i++)
//     {
//         auto &desc = windows_[i];
//         if (desc.sdlWin && desc.sdlWinID == sdlWinId)
//         {
//             SDL_DestroyWindow(desc.sdlWin);
//             desc = WindowImpl();
//             numWindows_ -= 1;
//             return VaneStat::OK;
//         }
//     }

//     return VaneStat::INVALID;
// }

