#include <cstdio>

#include <vane.hpp>
#include "vane/gameobject.hpp"
#include "vane/component.hpp"
#include "vane/port.hpp"

// #include "vane/message.hpp"
// static vane::TxMsgEndpoint          tx_opctrl;
// static RxSamplePortT<vane::OpState> rx_opstat;
static vane::TxSamplePort<vane::OpCtrl> opAuthTx;


int main(int argc, char **argv)
{
    using namespace vane;

    vane::Platform plat;
    auto *win0 = plat.makeIoDevice<Window>("Window 1", 1024, 1024);
    // auto *kb = plat->addIoDevice<iolib::Keyboard>();
    // auto *ms = plat->addIoDevice<iolib::Mouse>();

    GameObject player;
    player.addComponent<GraphicsComponent>();
    // player.addComponent<KeybdIoComponent>();
    // player.addComponent<MouseIoComponent>();
    // player.addComponent<PhysicsComponent>();
    // player.addComponent<GraphicsComponent>();

    while (plat.running())
    {
        plat.update();
        player.update();

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

