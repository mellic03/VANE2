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
    virtual void onMsgRecv(vane::srvmsg_t msg) final
    {
        using namespace vane::gfxapi;

        printf("[GameService::onMsgRecv] msg=%d\n", msg);
    }
};




int main(int argc, char **argv)
{
    using namespace vane;

    vane::Platform plat;
    auto *gfx  = plat.registerService<gfxapi::RenderEngine>("Game Name", 1024, 1024);
    auto *io   = plat.registerService<ioapi::IoApi>();
    auto *game = plat.registerService<GameService>();

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

