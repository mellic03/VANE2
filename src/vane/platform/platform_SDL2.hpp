#pragma once
#include "platform.hpp"

namespace vane
{
    class PlatformSDL2: public vane::Platform
    {
    public:
        virtual Window *createWindow(const char *name, int w, int h) final;
        virtual VaneStatus destroyWindow(Window *window) final;

    };
}



