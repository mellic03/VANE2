#include <cstdio>
#include "vane/platform/platform_SDL3.hpp"
#include "vane/vanelog.hpp"
// #include "vane/world.hpp"

int main(int argc, char **argv)
{
    vane::Platform *plat = new vane::PlatformSDL3();

    auto winId = plat->createWindow("Test Program", 512, 512);
    if (winId == vane::VANEID_NONE)
    {
        VLOG_FATAL("Failed to create window");
        return 1;
    }

    while (plat->running())
    {
        plat->update();
    }

    return 0;
}
