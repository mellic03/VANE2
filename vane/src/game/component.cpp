#include "component.hpp"
#include "vane/log.hpp"

void vane::KbInputComponent::update()
{
    static glm::vec3 impulse;

    if (0 || 1)
    {
        impulse = glm::vec3(0.0f, 2.523f, 0.0f);
        ComponentMessage msg = {
            .type    = PhysicsComponent::msgTypeID(),
            .subtype = PhysicsComponent::CMD_IMPULSE,
            .data    = (void*)&impulse
        };
        mObject->sendmsg(this, msg);
    }
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

    mObject->mAcc = G;
    mObject->mVel += mObject->mAcc;
    mObject->mPos += mObject->mVel;
}

void vane::PhysicsComponent::recvmsg(const ComponentMessage &msg)
{
    if (msg.type != msgTypeID())
    {
        return;
    }

    switch (msg.subtype)
    {
        case PhysicsComponent::CMD_DUMMY:
            break;

        case PhysicsComponent::CMD_IMPULSE:
            mObject->mVel += *static_cast<glm::vec3*>(msg.data);
            break;
    }
}



void vane::GraphicsComponent::update()
{

}

void vane::GraphicsComponent::recvmsg(const ComponentMessage &msg)
{
    if (msg.type != msgTypeID())
    {
        return;
    }
}


