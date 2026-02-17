#pragma once
#include "vane/vanetype.hpp"

namespace vane
{
    class Platform
    {
    public:
        struct Window
        {
            const char *name;
            int x, y, w, h;
            void *impl;
        };

        virtual Window *createWindow(const char *name, int w, int h) = 0;
        virtual VaneStatus destroyWindow(Window*) = 0;
        // virtual void *resizeWindow(void*, int w, int h) = 0;

    private:
        
    };
}
