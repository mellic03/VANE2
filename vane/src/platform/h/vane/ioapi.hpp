#pragma once

#include "vane/service.hpp"


namespace vane::ioapi
{
    struct IoApiMsg: public SrvMsg
    {
        static constexpr srvmsg_t NONE         = 256;
        static constexpr srvmsg_t UPDATE_MOUSE = NONE + 1;
    };

    class IoApi;
}


class vane::ioapi::IoApi: public vane::Service
{
public:
    virtual void onUpdate() final;
    virtual void onShutdown() final;
    virtual void onMsgRecv(srvmsg_t) final;

private:
    struct MouseInfo {
        float x, y, z, w;
    } mMouse;
};