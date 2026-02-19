#include "container.hpp"
#include "interface/icomponent.hpp"


void vane::Container::update()
{
    for (iComponent *C: mComponentList)
    {
        C->update();
    }
}


void vane::Container::sendmsg(iComponent *origin, const void *msg, size_t msgsz)
{
    for (iComponent *C: mComponentList)
    {
        if (C != origin)
        {
            C->recvmsg(msg, msgsz);
        }
    }
}


using namespace vane;

Container::iComponentList::iterator::iterator(iComponent *C)
:   mC(C)
{

}

Container::iComponentList::iterator::iterator(const iterator &I)
:   mC(I.mC)
{

}

Container::iComponentList::iterator&
Container::iComponentList::iterator::operator++()
{
    mC = mC->mNext;
    return *this;
};

Container::iComponentList::iterator
Container::iComponentList::iterator::operator++(int)
{
    return iterator(mC->mNext);
};
