#include <SDL3/SDL.h>
#include "gl.hpp"
#include <set>


namespace gpulib_gl
{
    struct WindowImpl
    {
        static constexpr size_t MAX_WINDOWS = 8;
        static inline int32_t numWindows_ = 0;

        SDL_Window   *mSdlWin;
        SDL_GLContext mSdlGlCtx;
        SDL_WindowID  mSdlWinID;

        WindowImpl(const char *name, int x, int y, int w, int h);
    };
}


gpulib_gl::WindowImpl::WindowImpl(const char *name, int x, int y, int w, int h)
{
    mSdlWin = SDL_CreateWindow(name, 1024, 1024, SDL_WINDOW_OPENGL);
    if (mSdlWin == NULL)
    {
        VLOG_ERROR("{}", SDL_GetError());
        return VANEID_NONE;
    }
}



vane::vaneid_t vane::Platform::createWindow(const char *name, int w, int h)
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

    SDL_SetWindowPosition(sdlWin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    GLint major, minor;
    gl::GetIntegerv(GL_MAJOR_VERSION, &major);
    gl::GetIntegerv(GL_MINOR_VERSION, &minor);
    VLOG_INFO("Device supports up to OpenGL {}.{}", major, minor);

    vaneid_t sdlWinId = WindowImpl_alloc(sdlWin, sdlGlCtx);
    VLOG_INFO("Created window {}", sdlWinId);

    return sdlWinId;
}


vane::VaneStat vane::Platform::destroyWindow(vane::vaneid_t sdlWinId)
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

