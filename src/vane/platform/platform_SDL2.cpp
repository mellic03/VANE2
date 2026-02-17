#include "platform_SDL2.hpp"
#include <SDL2/SDL.h>

struct VaneWindow_SDL2
{
    
};


vane::Platform::Window *vane::PlatformSDL2::createWindow(const char *name, int w, int h)
{
    SDL_Window *win = SDL_CreateWindow(name, 0, 0, w, h, 0);

    return (void*)win;
}

vane::VaneStatus vane::PlatformSDL2::destroyWindow(vane::Platform::Window *win)
{
    SDL_DestroyWindow((SDL_Window*)(win->impl));
    return VaneStatus::OK;
}

