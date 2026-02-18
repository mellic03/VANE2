#include "platform_impl.hpp"
#include "gpu_gl.hpp"
#include "vane/log.hpp"

#include <SDL3/SDL.h>
#include <vector>
#include <filesystem>

static std::vector<vane::gpu_gl::WindowImpl*> cull_list_;


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
        exit(1);
    }
    VLOG_INFO("SDL3 Initialized");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

        // SDL_Window *eWin = SDL_GetWindowFromEvent(&e);
        // if (e.type == SDL_EVENT_QUIT)
        // {
        //     if (winptr) destroyWindow(e.window.windowID);
        //     else        this->shutdown();
        // }

        // else if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        // {
        //     destroyWindow(e.window.windowID);
        // }

        // else if (e.type == SDL_EVENT_KEY_UP)
        // {
        //     if (e.key.key == SDLK_ESCAPE)
        //     {
        //         destroyWindow(e.window.windowID);
        //     }
        // }
    }

    // for (int i=0; i<WindowImpl::MAX_WINDOWS; i++)
    // {
    //     auto &desc = windows_[i];
    //     if (desc.isInUse())
    //     {
    //         SDL_GL_MakeCurrent(desc.sdlWin, desc.sdlGlCtx);
    //         gl::ClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    //         gl::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //         SDL_GL_SwapWindow(desc.sdlWin);
    //     }
    // }

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
    auto *win = new gpu_gl::WindowImpl(
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


vane::VaneStat vane::Platform::destroyWindow_ptr(gpu_gl::WindowImpl *winptr)
{
    if (mWindows.contains(winptr))
    {
        cull_list_.push_back(winptr);
        return VaneStat::OK;
    }

    VLOG_ERROR("Deletion of non-existent window ({})", winptr->mSdlWinID);
    return VaneStat::INVALID;
}


vane::gpu_gl::WindowImpl *vane::Platform::getWindow(vaneid_t sdlWinId)
{
    for (auto *win: mWindows)
        if (win->mSdlWinID == sdlWinId)
            return win;
    VLOG_WARN("Access of non-existent window ({})", sdlWinId);
    return nullptr;
}

