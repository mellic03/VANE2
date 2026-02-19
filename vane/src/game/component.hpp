#pragma once

#include "interface/icomponent.hpp"


namespace vane
{
    class iHwIoComponent;
    class KeybdIoComponent;
    class MouseIoComponent;

    class PhysicsComponent;
    class GraphicsComponent;
}



class vane::iHwIoComponent: public iComponent
{
public:
    using iComponent::iComponent;
    virtual ~iHwIoComponent() {  };
};


class vane::KeybdIoComponent: public iHwIoComponent
{
public:
    using iHwIoComponent::iHwIoComponent;
    virtual ~KeybdIoComponent() {  };
    virtual void update() override;
    virtual void recvmsg(const void*, size_t) override;

private:

};


class vane::MouseIoComponent: public iHwIoComponent
{
public:
    using iHwIoComponent::iHwIoComponent;
    virtual ~MouseIoComponent() {  };
    virtual void update() override;
    virtual void recvmsg(const void*, size_t) override;

private:

};




class vane::PhysicsComponent: public iComponent
{
public:
    static constexpr int32_t CMD_DUMMY   = 0x00;
    static constexpr int32_t CMD_IMPULSE = 0x03;

    using iComponent::iComponent;
    virtual void update() override;
    virtual void recvmsg(const void*, size_t) override;

private:
    float mInvMass = 0.01f;
};



class vane::GraphicsComponent: public iComponent
{
public:
    using iComponent::iComponent;
    virtual void update() override;
    virtual void recvmsg(const void*, size_t) override;

private:
    int mModelId = 3;
};

