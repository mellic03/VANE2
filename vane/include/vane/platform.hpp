#pragma once
#include "vane/type.hpp"
#include <set>

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
        VaneStat destroyWindow_ptr(PlatformWindowType*);
        PlatformWindowType *getWindow(vaneid_t);
    private:
        bool mRunning;
        std::set<PlatformWindowType*> mWindows;

    };
}

