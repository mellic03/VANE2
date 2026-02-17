#include <cstdio>
#include "vane/platform.hpp"
#include "vane/log.hpp"
// #include "vane/world.hpp"

int main(int argc, char **argv)
{
    vane::Platform *plat = new vane::Platform();

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
