#include <cstdio>

#include "vane/platform/platform_SDL3.hpp"
#include "vane/platform/impl_sdl3.hpp"
#include <vane/game/gameobject.hpp>

// #include "vane/message.hpp"
// static vane::TxMsgEndpoint          tx_opctrl;
// static RxSamplePortT<vane::OpState> rx_opstat;


int main(int argc, char **argv)
{
    using namespace vane;

    Platform::Impl impl = {
        .init = PlatformSDL3_init,
        .poll = PlatformSDL3_poll
    };

    Platform plat(impl);
    // tx_opctrl.sendmsg_bcast(OpCtrl::Terminate);

    auto *win0 = plat.iodev_create<vane::PlatformWindow>("Window 1", 1024, 1024);
    // auto *kb = plat->addIoDevice<iolib::Keyboard>();
    // auto *ms = plat->addIoDevice<iolib::Mouse>();

    // GameObject player;
    // player.addComponent<KeybdIoComponent>();
    // player.addComponent<MouseIoComponent>();
    // player.addComponent<PhysicsComponent>();
    // player.addComponent<GraphicsComponent>();

    while (plat.active())
    {
        plat.update();
        // player.update();

        // if (kb->keyWasPressed(SDL_SCANCODE_E))
        //     printf("E PRESSED\n");
        // if (kb->keyWasReleased(SDL_SCANCODE_E))
        //     printf("E RELEASED\n");

        // if (ms->mouseWasPressed(iolib::Mouse::Button::LEFT))
        //     printf("Mouse LEFT PRESSED\n");
        // if (ms->mouseWasReleased(iolib::Mouse::Button::LEFT))
        //     printf("Mouse LEFT RELEASED\n");
    }

    return 0;
}

