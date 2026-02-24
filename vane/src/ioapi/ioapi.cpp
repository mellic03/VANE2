#include "vane/ioapi.hpp"
#include "vane/gfxapi.hpp"
#include <SDL3/SDL.h>

using namespace vane;


void IoApi::onUpdate()
{
    SDL_GetMouseState(&mMouse.x, &mMouse.y);

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            srvCmdToAll(command::SRV_SHUTDOWN, nullptr);
            return;
        }

        if (SDL_GetWindowFromEvent(&e))
        {
            srvMsgToSrv<gfxapi::RenderEngine>(message::IO_WIN_EVENT, (void*)(&e));
            // if (auto *gfx = getService<gfxapi::RenderEngine>())
            // {
            //     gfx.on
            // }
        }

        if (e.type == SDL_EVENT_KEY_UP)
        {
            srvMsgToSrv<gfxapi::RenderEngine>(message::IO_KEYUP_EVENT, (void*)(&e));
        }

        if (e.type == SDL_EVENT_KEY_DOWN)
        {
            srvMsgToSrv<gfxapi::RenderEngine>(message::IO_KEYDOWN_EVENT, (void*)(&e));
        }
    }

}


void IoApi::onShutdown()
{

}


void IoApi::onMsgRecv(vane::message msg, void *arg)
{
    switch (msg)
    {
        default:
            return;
    }

}



void IoApi::onCmdRecv(vane::command cmd, void *arg)
{
    switch (cmd)
    {
        default:
            return;
    }

}


