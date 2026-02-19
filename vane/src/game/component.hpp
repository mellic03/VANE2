#pragma once

#include "interface/icomponent.hpp"
#include <glm/glm.hpp>


namespace vane
{
    class iHwIoComponent;
    class KeybdIoComponent;
    class MouseIoComponent;

    class GraphicsComponent;
    class PhysicsComponent;
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



class vane::GraphicsComponent: public iComponent
{
public:
    using iComponent::iComponent;
    virtual void update() override;
    virtual void recvmsg(const void*, size_t) override;

private:
    int mModelId = 3;
};



class vane::PhysicsComponent: public iComponent
{
private:
    glm::vec3 mAcc;
    glm::vec3 mVel;
    float mInvMass = 0.01f;

public:
    PhysicsComponent(GameObject *obj)
    :   iComponent(obj), mAcc(0.0f), mVel(0.0f) {  }

    virtual void update() override;
    virtual void recvmsg(const void*, size_t) override;
    // static constexpr int32_t CMD_DUMMY   = 0x00;
    // static constexpr int32_t CMD_IMPULSE = 0x03;

};
