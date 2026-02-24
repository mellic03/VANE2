#pragma once

#include <SDL3/SDL.h>
#include "vane/gfxapi.hpp"


struct vane::gfxapi::RenderEngine::Window
{
    friend class RenderEngine;
public:
    Window(const char *name, int w, int h);
    Window(const Window&) = delete;
    Window &operator=(const Window&) = delete;
    ~Window();
    
    void onUpdate();
    void onEvent(const SDL_Event&);
    // void setProgram(const RenderProgramPtr&);
    // RenderProgramPtr getProgram();

private:
    SDL_Window   *mSdlWin;
    SDL_GLContext mSdlGlCtx;
    SDL_WindowID  mSdlWinID;

    int32_t mGlVersionMajor;
    int32_t mGlVersionMinor;

    uint32_t mVAO;


    void _makeCurrent();
    void _swap();

};

