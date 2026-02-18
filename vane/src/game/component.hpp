#pragma once

#include "gameobject.hpp"


namespace vane
{
    class iInputComponent;
    class KbInputComponent;
    class PhysicsComponent;
    class GraphicsComponent;
}


class vane::iInputComponent: public iComponent
{
public:
    using iComponent::iComponent;
    virtual ~iInputComponent() {  }
};


class vane::KbInputComponent: public iInputComponent
{
public:
    static int32_t msgTypeID() { static int32_t value = ComponentMessage::newMessageTypeID(); return value; }

    using iInputComponent::iInputComponent;
    virtual ~KbInputComponent() {  }
    virtual void update() override;
    virtual void recvmsg(const vane::ComponentMessage &msg) override;

private:
};



class vane::PhysicsComponent: public iComponent
{
public:
    static int32_t msgTypeID() { static int32_t value = ComponentMessage::newMessageTypeID(); return value; }
    static constexpr int32_t CMD_DUMMY   = 0x00;
    static constexpr int32_t CMD_IMPULSE = 0x03;

    using iComponent::iComponent;
    virtual void update() override;
    virtual void recvmsg(const ComponentMessage &msg) override;

private:
    float mInvMass = 0.01f;
};



class vane::GraphicsComponent: public iComponent
{
public:
    static int32_t msgTypeID() { static int32_t value = ComponentMessage::newMessageTypeID(); return value; }

    using iComponent::iComponent;
    virtual void update() override;
    virtual void recvmsg(const ComponentMessage &msg) override;

private:
    int mModelId = 3;
};

