#include "platform_SDL3.hpp"
#include "vane/log.hpp"
#include <SDL3/SDL.h>
#include "../graphics/gl.hpp"


struct WindowImpl
{
    static constexpr size_t MAX_WINDOWS = 8;
    static inline int32_t numWindows_ = 0;

    SDL_Window   *sdlWin;
    SDL_GLContext sdlGlCtx;
    SDL_WindowID  sdlWinID;

    WindowImpl(): sdlWin(nullptr), sdlGlCtx(nullptr), sdlWinID(0) {  }

    bool isInUse() { return (bool)sdlWin; }
    bool notInUse() { return !isInUse(); }

    void init(SDL_Window *win, SDL_GLContext glctx)
    {
        sdlWin = win;
        sdlGlCtx = glctx;
        sdlWinID = SDL_GetWindowID(win);
        numWindows_ += 1;
    }

    void deinit()
    {
        sdlWin = nullptr;
        sdlGlCtx = nullptr;
        sdlWinID = 0;
        numWindows_ -= 1;
    }
};

static WindowImpl windows_[WindowImpl::MAX_WINDOWS];

static vane::vaneid_t WindowImpl_alloc(SDL_Window*, SDL_GLContext);
static vane::VaneStat WindowImpl_free(SDL_WindowID);




vane::PlatformSDL3::PlatformSDL3()
:   mRunning(true)
{
    if (false == SDL_Init(SDL_INIT_VIDEO))
    {
        VLOG_FATAL("{}", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
        auto &desc = windows_[i];
        if (desc.isInUse())
        {
            SDL_GL_MakeCurrent(desc.sdlWin, desc.sdlGlCtx);
            gl::ClearColor(1.0f, 0.5f, 0.0f, 1.0f);
            gl::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SDL_GL_SwapWindow(desc.sdlWin);
        }
    }

}


vane::vaneid_t vane::PlatformSDL3::createWindow(const char *name, int w, int h)
{
    if (WindowImpl::numWindows_ == WindowImpl::MAX_WINDOWS)
    {
        return VANEID_NONE;
    }

    SDL_Window *sdlWin = SDL_CreateWindow(name, 1024, 1024, SDL_WINDOW_OPENGL);
    if (sdlWin == nullptr)
    {
        VLOG_ERROR("{}", SDL_GetError());
        return VANEID_NONE;
    }

    SDL_GLContext sdlGlCtx = SDL_GL_CreateContext(sdlWin);
    if (sdlGlCtx == nullptr)
    {
        VLOG_ERROR("{}", SDL_GetError());
        return VANEID_NONE;
    }

    if (!gladLoadGL())
    {
        VLOG_FATAL("gladLoadGL error");
        exit(1);
    }

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    VLOG_INFO("Device supports up to OpenGL {}.{}", major, minor);

    // SDL_Surface *sdlSurf = SDL_GetWindowSurface(sdlWin);
    // if (sdlSurf == nullptr)
    // {
    //     VLOG_ERROR("{}", SDL_GetError());
    //     SDL_DestroyWindow(sdlWin);
    //     return VANEID_NONE;
    // }

    SDL_SetWindowPosition(sdlWin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    vaneid_t sdlWinId = WindowImpl_alloc(sdlWin, sdlGlCtx);
    VLOG_INFO("Created window {}", sdlWinId);

    return sdlWinId;
}


vane::VaneStat vane::PlatformSDL3::destroyWindow(vane::vaneid_t sdlWinId)
{
    VaneStat status = WindowImpl_free(sdlWinId);
    if (status == VaneStat::OK)
        VLOG_INFO("Destroyed window {}", sdlWinId);
    else
        VLOG_WARN("Invalid WindowID {}", (uint32_t)sdlWinId);
    return VaneStat::OK;

}




static vane::vaneid_t WindowImpl_alloc(SDL_Window *sdlWin, SDL_GLContext sdlGlCtx)
{
    using namespace vane;

    WindowImpl *desc = &(windows_[0]);
    for (size_t i=0; i<WindowImpl::MAX_WINDOWS; i++)
    {
        if (desc->notInUse())
        {
            desc->init(sdlWin, sdlGlCtx);
            return vaneid_t(desc->sdlWinID);
        }
        desc++;
    }

    return VANEID_NONE;
}


static vane::VaneStat WindowImpl_free(SDL_WindowID sdlWinId)
{
    using namespace vane;

    WindowImpl *desc = &(windows_[0]);
    for (int i=0; i<WindowImpl::MAX_WINDOWS; i++)
    {
        if (desc->isInUse() && desc->sdlWinID == sdlWinId)
        {
            SDL_DestroyWindow(desc->sdlWin);
            desc->deinit();
            return VaneStat::OK;
        }
        desc++;
    }

    return VaneStat::INVALID;
}

