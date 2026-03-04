#include <cstdio>

#include <vane.hpp>
#include <vane/gfxapi.hpp>
#include <vane/ioapi.hpp>
#include "vane/gameobject.hpp"
#include "vane/component.hpp"
#include "vane/port.hpp"


class GameService: public vane::Service
{
public:
    virtual void onUpdate() final {  }
    virtual void onMsgRecv(vane::message msg, void*) final
    {
        using namespace vane::gfxapi;
        printf("[GameService::onMsgRecv] msg=%d\n", static_cast<int>(msg));
    }
};



int main(int argc, char **argv)
{
    using namespace vane;

    (void)argc;
    (void)argv;

    // ioapi::IoApi   io;
    // gfxapi::GfxApi gfx;

    vane::Platform plat;
    auto *gfx  = plat.registerService<GfxApi>("Game Name", 1024, 1024);
    auto *io   = plat.registerService<IoApi>();
    auto *game = plat.registerService<GameService>();
    
    (void)io;
    (void)game;

    auto *cam = gfx->createCamera(512, 512);
    (void)cam;

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

