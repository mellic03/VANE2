#include "component.hpp"
#include "vane/log.hpp"

void vane::KbInputComponent::update()
{
    ComponentMessage msg = {
        .type = PhysicsComponent::msgTypeID(),
        .data = (void*)0x2026
    };
    mObject->sendmsg(this, msg);
}

void vane::KbInputComponent::recvmsg(const ComponentMessage &msg)
{
    if (msg.type != msgTypeID())
    {
        return;
    }

    VLOG_INFO("KbInputComponent::recvmsg type={}, data={:#x}", msg.type, (uintptr_t)(msg.data));
}



void vane::PhysicsComponent::update()
{
    static constexpr glm::vec3 G(0.0f, -9.81f, 0.0f);

    GameObject &obj = *mObject;
    obj.mAcc = G;
    obj.mVel += obj.mAcc;
    obj.mPos += obj.mVel;

    ComponentMessage msg = {
        .type = GraphicsComponent::msgTypeID(),
        .data = nullptr
    };
    mObject->sendmsg(this, msg);
}

void vane::PhysicsComponent::recvmsg(const ComponentMessage &msg)
{
    if (msg.type != msgTypeID())
    {
        return;
    }
}



void vane::GraphicsComponent::update()
{
    ComponentMessage msg = {
        .type = PhysicsComponent::msgTypeID(),
        .data = nullptr
    };
    mObject->sendmsg(this, msg);
}

void vane::GraphicsComponent::recvmsg(const ComponentMessage &msg)
{
    if (msg.type != msgTypeID())
    {
        return;
    }
}


