#pragma once
#include <SDL3/SDL.h>

namespace vane
{
    using PlatformEventType = SDL_Event;
    class Platform;
}

vane::OpState PlatformSDL3_init();
bool PlatformSDL3_poll(vane::Platform &plat, vane::PlatformEventType *e);
