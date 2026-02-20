#include "vane/platform.hpp"
#include "gl_bindings.hpp"
#include "vane/log.hpp"

#include <vector>
#include <set>
#include <filesystem>

static std::set<vane::PlatformWindow*> cull_set_;


vane::Platform::Platform()
:   mRunning(true)
{
    std::filesystem::current_path(std::filesystem::path(SDL_GetBasePath()));

    if (false == SDL_Init(SDL_INIT_VIDEO))
        VLOG_FATAL("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8))
        VLOG_ERROR("{}", SDL_GetError());

    VLOG_INFO("SDL3 Initialized");
}


bool vane::Platform::running()
{
    return mRunning;
}


void vane::Platform::shutdown()
{
    VLOG_INFO("Shutdown initiated");

    for (auto *winptr: mWindows)
        delete winptr;
    mWindows.clear();

    mRunning = false;

    VLOG_INFO("Shutdown complete");
}


void vane::Platform::update()
{
    if (mWindows.empty())
    {
        this->shutdown();
        return;
    }

    for (auto *winptr: cull_set_)
    {
        mWindows.erase(winptr);
        delete winptr;
    }
    cull_set_.clear();

    for (auto *winptr: mWindows)
        winptr->update();

    for (auto *iodev: mIoDevices)
        iodev->update();

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            this->shutdown();
            break;
        }

        if (!SDL_GetWindowFromEvent(&e))
            continue;

        if (auto *winptr = getWindow(e.window.windowID))
            winptr->updateEvent(e);

        for (auto *iodev: mIoDevices)
            iodev->updateEvent(e);
    }
}


vaneid_t vane::Platform::createWindow(const char *name, int w, int h)
{
    auto *win = new PlatformWindow(
        this, name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h
    );
    mWindows.insert(win);
    return win->mSdlWinID;
}


vane::VaneStat vane::Platform::destroyWindow(vaneid_t sdlWinId)
{
    for (auto *winptr: mWindows)
        if (winptr->mSdlWinID == sdlWinId)
            return destroyWindow_ptr(winptr);
    VLOG_ERROR("Deletion of non-existent window ({})", (uint32_t)sdlWinId);
    return VaneStat::INVALID;
}


vane::VaneStat vane::Platform::destroyWindow_ptr(PlatformWindow *winptr)
{
    if (mWindows.contains(winptr))
    {
        cull_set_.insert(winptr);
        return VaneStat::OK;
    }

    VLOG_ERROR("Deletion of non-existent window ({})", winptr->mSdlWinID);
    return VaneStat::INVALID;
}


vane::PlatformWindow *vane::Platform::getWindow(vaneid_t sdlWinId)
{
    for (auto *win: mWindows)
        if (win->mSdlWinID == sdlWinId)
            return win;
    VLOG_WARN("Access of non-existent window ({})", sdlWinId);
    return nullptr;
}

