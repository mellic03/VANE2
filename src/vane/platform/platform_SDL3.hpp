#pragma once
#include "vane/platform.hpp"
#include "vane/ds/inplace_list.hpp"


namespace vane
{
    class PlatformSDL3: public vane::Platform
    {
    public:
        PlatformSDL3();

        virtual bool running() final;
        virtual void shutdown() final;
        virtual void update() final;

        virtual vaneid_t createWindow(const char *name, int w, int h) final;
        virtual VaneStat destroyWindow(vaneid_t) final;

    private:
        bool mRunning;
        // vane::inplace_list<Platform::Window, 8> mWindows;

    };
}

