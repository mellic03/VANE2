#include <cstdio>

#include "vane/platform.hpp"
#include "iolib/iolib.hpp"
#include "vane/log.hpp"
#include "vane/util/metric.hpp"

#include "game/gameobject.hpp"
#include "game/component.hpp"
#include "game/world.hpp"

// #include "vane/dsa/bump_allocator.hpp"
// BumpAllocator BA(64 * metric::MEGA);
// SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1)


#include "vane/dsa/message.hpp"

struct RxPort: public vane::RxMsgEndpoint
{
    virtual void recvmsg(const void *msg, size_t msgsz) final
    {
        printf("[RxPort::recvmsg] 0x%lx, %lu\n", (size_t)msg, msgsz);
    }
};

void testfn()
{
    vane::TxMsgEndpoint txer;
    RxPort rxers[8];

    for (int i=0; i<8; i++)
    {
        txer.rxopen(&rxers[i]);
    }

    for (int i=0; i<4; i++)
    {
        printf("i==%d\n", i);
        txer.sendmsg_bcast(nullptr, 16*i);
    }
}

int main(int argc, char **argv)
{
    using namespace vane;

    testfn();
    return 1;

    vane::World world;

    GameObject player;
    player.addComponent<KeybdIoComponent>();
    player.addComponent<MouseIoComponent>();
    player.addComponent<PhysicsComponent>();
    player.addComponent<GraphicsComponent>();

    auto *plat = new vane::Platform();
    auto *kb = plat->addIoDevice<iolib::Keyboard>();
    auto *ms = plat->addIoDevice<iolib::Mouse>();

    if (VANEID_NONE == plat->createWindow("Window 1", 512, 512))
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

