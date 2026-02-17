#pragma once
#include "vane/vanetype.hpp"

namespace vane
{
    class Platform
    {
    public:
        Platform() {  }

        virtual bool running() = 0;
        virtual void shutdown() = 0;
        virtual void update() = 0;

        virtual vaneid_t createWindow(const char *name, int w, int h) = 0;
        virtual VaneStat destroyWindow(vaneid_t) = 0;
        // virtual void *resizeWindow(void*, int w, int h) = 0;

    private:

    };
}
