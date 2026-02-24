#include "vane/ioapi.hpp"
#include "vane/gfxapi.hpp"
#include <SDL3/SDL.h>

using namespace vane::ioapi;


void IoApi::onUpdate()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            srvMsgToAll(SrvMsg::SHUTDOWN);
            return;
        }

        if (SDL_GetWindowFromEvent(&e))
        {
            srvRunCmd<gfxapi::RenderEngine>(gfxapi::GfxApiMsg::WIN_EVENT, (void*)(&e));
            // if (auto *gfx = getService<gfxapi::RenderEngine>())
            // {
            //     gfx.on
            // }
        }

        if (e.type == SDL_EVENT_KEY_DOWN)
        {
            srvRunCmd<gfxapi::RenderEngine>(gfxapi::GfxApiMsg::KEYDOWN_EVENT, (void*)(&e));
        }
    }

}


void IoApi::onShutdown()
{

}


void IoApi::onMsgRecv(srvmsg_t msg)
{
    printf("[IoApi::onMsgRecv] msg=%d\n", msg);

    switch (msg)
    {
        case IoApiMsg::NONE:
            break;
        case IoApiMsg::UPDATE_MOUSE:
            SDL_GetMouseState(&mMouse.x, &mMouse.y);
            break;
        default:
            return;
    }

}


