#include "gameobject.hpp"


vane::GameObject::GameObject()
:   mCompHead(nullptr),
    mAcc(0.0f), mVel(0.0f), mPos(0.0f)
{

}


void vane::GameObject::update()
{
    iComponent *comp = mCompHead;
    while (comp)
    {
        comp->update();
        comp = comp->mNext;
    }
}


void vane::GameObject::sendmsg(iComponent *origin, const ComponentMessage &msg)
{
    iComponent *comp = mCompHead;
    while (comp)
    {
        if (comp != origin)
        {
            comp->recvmsg(msg);
        }

        comp = comp->mNext;
    }
}


