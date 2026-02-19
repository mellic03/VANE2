#include "gameobject.hpp"
#include <cstdio>


vane::GameObject::GameObject()
:   mAcc(0.0f), mVel(0.0f), mPos(0.0f)
{
    mComponentList.head = nullptr;

}


void vane::GameObject::update()
{
    for (iComponent *C: mComponentList)
    {
        C->update();
    }
}


void vane::GameObject::sendmsg(iComponent *origin, const void *msg, size_t msgsz)
{
    for (iComponent *C: mComponentList)
    {
        if (C != origin)
        {
            C->recvmsg(msg, msgsz);
        }
    }
}



