#include <cstdio>

#include <vane.hpp>
#include <vane/gfxapi.hpp>
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
    auto *gfx = plat.createObject<gfxapi::RenderEngine>("Game Name", 1024, 1024);
          gfx->createRenderProgram("data/shader/quad.vert", "data/shader/quad.frag");
    // auto win = std::make_shared<gfxapi::Window>(gfx, "Main Window", 1024, 1024);
    //      win->setFramebuffer(std::make_shared<gfxapi::Framebuffer>(gfx));
    //      win->getFramebuffer()->setTextureDst(std::make_shared<gfxapi::Texture>(gfx, 1024, 1024, nullptr));
    //      win->setProgram(
    //         std::make_shared<gfxapi::ShaderProgram>(gfx, "data/shader/quad.vert", "data/shader/quad.frag")
    //     );

    // auto *lmao = plat.createObject<LmaoType>();
    //       lmao->mWindow = win;

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

