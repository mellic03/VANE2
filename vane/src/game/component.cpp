#include "component.hpp"
#include "vane/log.hpp"
#include "vane/util/vanetypeid.hpp"



void vane::KeybdIoComponent::update()
{
    printf("[KeybdIoComponent::update]\n");
}

void vane::KeybdIoComponent::recvmsg(const void *msg, size_t msgsz)
{

}



void vane::MouseIoComponent::update()
{
    printf("[MouseIoComponent::update]\n");
}

void vane::MouseIoComponent::recvmsg(const void *msg, size_t msgsz)
{

}




void vane::PhysicsComponent::update()
{
    printf("[PhysicsComponent::update]\n");

    // static constexpr glm::vec3 G(0.0f, -9.81f, 0.0f);

    // mObject->mAcc = G;
    // mObject->mVel += mObject->mAcc;
    // mObject->mPos += mObject->mVel;
}

void vane::PhysicsComponent::recvmsg(const void *msg, size_t msgsz)
{
    // if (msg.type != vaneTypeID<PhysicsComponent>())
    // {
    //     return;
    // }

    // switch (msg.subtype)
    // {
    //     case PhysicsComponent::CMD_DUMMY:
    //         break;

    //     case PhysicsComponent::CMD_IMPULSE:
    //         mObject->mVel += *static_cast<glm::vec3*>(msg.data);
    //         break;
    // }
}



void vane::GraphicsComponent::update()
{
    printf("[GraphicsComponent::update]\n");

}

void vane::GraphicsComponent::recvmsg(const void *msg, size_t msgsz)
{

}


