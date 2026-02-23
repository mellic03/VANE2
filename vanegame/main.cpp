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


struct LmaoType: public vane::ObjectManager::Object
{
    std::shared_ptr<vane::gfxapi::Window> mWindow;

    using Object::Object;
    // LmaoType(std::shared_ptr<vane::gfxapi::Window> win)
    // :   mWindow(win) {  };
    virtual void onUpdate() final { mWindow->onUpdate(); }
    virtual void onEvent(void *p) final { mWindow->onEvent(p); }
};


int main(int argc, char **argv)
{
    using namespace vane;

    vane::Platform plat;

    auto gfx = vane::gfxapi::getGfxApi();
    auto fb  = gfx->createFramebuffer();
         fb->setTextureDst(gfx->createTexture(1024, 1024, nullptr));

    auto *lmao = plat.createObject<LmaoType>();
          lmao->mWindow = gfx->getMainWindow();

    // ree->donothing();

    // auto *win0 = plat.add<Window>("Window 1", 1024, 1024);
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

