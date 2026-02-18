#include "platform_impl.hpp"
#include "vane/log.hpp"

#include <SDL3/SDL.h>
#include <vector>
#include <filesystem>

static std::vector<vane::WindowImplType*> cull_list_;


vane::Platform::Platform()
:   mRunning(true)
{
    {
        namespace fs = std::filesystem;
        fs::current_path(fs::path(SDL_GetBasePath()));
    }

    if (false == SDL_Init(SDL_INIT_VIDEO))
    {
        VLOG_FATAL("{}", SDL_GetError());
    }

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
    {
        cull_list_.push_back(winptr);
    }

    while (!cull_list_.empty())
    {
        auto *winptr = cull_list_.back();
                       cull_list_.pop_back();
        mWindows.erase(winptr);
        delete winptr;
    }

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

    for (auto *winptr: mWindows)
    {
        winptr->update();
    }

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            this->shutdown();
        }

        if (!SDL_GetWindowFromEvent(&e))
        {
            continue;
        }

        if (auto *winptr = getWindow(e.window.windowID))
        {
            winptr->updateEvent(e);
        }
    }

    while (!cull_list_.empty())
    {
        auto *winptr = cull_list_.back();
                       cull_list_.pop_back();
        mWindows.erase(winptr);
        delete winptr;
    }
}


vane::vaneid_t vane::Platform::createWindow(const char *name, int w, int h)
{
    auto *win = new WindowImplType(
        this, name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h
    );
    mWindows.insert(win);
    return win->mSdlWinID;
}


vane::VaneStat vane::Platform::destroyWindow(vane::vaneid_t sdlWinId)
{
    for (auto *winptr: mWindows)
    {
        if (winptr->mSdlWinID == sdlWinId)
        {
            return destroyWindow_ptr(winptr);
        }
    }

    VLOG_ERROR("Deletion of non-existent window ({})", (uint32_t)sdlWinId);
    return VaneStat::INVALID;
}


vane::VaneStat vane::Platform::destroyWindow_ptr(WindowImplType *winptr)
{
    if (mWindows.contains(winptr))
    {
        cull_list_.push_back(winptr);
        return VaneStat::OK;
    }

    VLOG_ERROR("Deletion of non-existent window ({})", winptr->mSdlWinID);
    return VaneStat::INVALID;
}


vane::WindowImplType *vane::Platform::getWindow(vaneid_t sdlWinId)
{
    for (auto *win: mWindows)
        if (win->mSdlWinID == sdlWinId)
            return win;
    VLOG_WARN("Access of non-existent window ({})", sdlWinId);
    return nullptr;
}

