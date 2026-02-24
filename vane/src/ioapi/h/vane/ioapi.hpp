#pragma once

#include "vane/service.hpp"


namespace vane
{
    class IoApi;
}


class vane::IoApi: public vane::Service
{
public:
    virtual void onUpdate() final;
    virtual void onShutdown() final;
    virtual void onMsgRecv(vane::message, void*) final;
    virtual void onCmdRecv(vane::command, void*) final;

private:
    struct MouseInfo {
        float x, y, z, w;
    } mMouse;
};

