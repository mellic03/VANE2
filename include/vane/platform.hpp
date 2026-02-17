#pragma once
#include "vane/type.hpp"

namespace vane
{
    class Platform
    {
    public:
        Platform();
        bool running();
        void shutdown();
        void update();
        vaneid_t createWindow(const char *name, int w, int h);
        VaneStat destroyWindow(vaneid_t);

    private:
        bool mRunning;
        // vane::inplace_list<Platform::Window, 8> mWindows;

    };
}

