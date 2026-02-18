#include <cstdio>

// #include "gfxlib/gfxlib.hpp"
#include "platform/platform_impl.hpp"
#include "iolib/iolib.hpp"
#include "vane/log.hpp"
#include "vane/dsa/bump_allocator.hpp"
#include "vane/util/metric.hpp"

#include "game/gameobject.hpp"
#include "game/component.hpp"


int main(int argc, char **argv)
{
    using namespace vane;
    // BumpAllocator BA(64 * metric::MEGA);

    GameObject player;
    player.addComponent<KbInputComponent>();
    player.addComponent<PhysicsComponent>();
    player.addComponent<GraphicsComponent>();

    auto *plat = new vane::Platform();
    auto *kb = plat->createIoDevice<iolib::Keyboard>();
    auto *ms = plat->createIoDevice<iolib::Mouse>();

    auto winId = plat->createWindow("Test Program", 512, 512);
    if (winId == VANEID_NONE)
    {
        VLOG_FATAL("Failed to create window");
        return 1;
    }

    while (plat->running())
    {
        plat->update();
        player.update();

        if (kb->keyWasPressed(SDL_SCANCODE_E))
            printf("E PRESSED\n");
        if (kb->keyWasReleased(SDL_SCANCODE_E))
            printf("E RELEASED\n");

        if (ms->mouseWasPressed(iolib::Mouse::Button::LEFT))
            printf("Mouse LEFT PRESSED\n");
        if (ms->mouseWasReleased(iolib::Mouse::Button::LEFT))
            printf("Mouse LEFT RELEASED\n");

        // printf("x: %f\n", ms->mousePos().x);
    }

    return 0;
}

