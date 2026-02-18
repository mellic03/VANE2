#include <cstdio>

#include "gfxlib/gfxlib.hpp"
#include "iolib/iolib.hpp"

#include "vane/log.hpp"
// #include "vane/world.hpp"

int main(int argc, char **argv)
{
    using namespace vane;

    auto *plat = new vane::Platform();
    auto *kb = plat->createIoDevice<iolib::Keyboard>();

    auto winId = plat->createWindow("Test Program", 512, 512);
    if (winId == VANEID_NONE)
    {
        VLOG_FATAL("Failed to create window");
        return 1;
    }

    while (plat->running())
    {
        plat->update();

        if (kb->keyPressed(SDL_SCANCODE_E))
        {
            printf("E PRESSED\n");
        }
        if (kb->keyReleased(SDL_SCANCODE_E))
        {
            printf("E RELEASED\n");
        }
    }

    return 0;
}
