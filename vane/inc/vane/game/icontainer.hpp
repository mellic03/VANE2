#pragma once

#include "icomponent.hpp"
#include "vane/dsa/linkedlist.hpp"
#include <type_traits>


namespace vane
{
    class iComponent;
    class iContainer;
}


class vane::iContainer
{
public:
    void update();
    void sendmsg(iComponent *origin, const void *msg, size_t msgsz);

    template <typename T>
    void sendmsg(iComponent *origin, const T &msg);

    template <typename T>
    void addComponent();

private:
    dsa::LinkedList<iComponent> mCmptList;

};



inline void vane::iContainer::update()
{
    for (iComponent *C: mCmptList)
    {
        C->update();
    }
}


inline void vane::iContainer::sendmsg(iComponent *origin, const void *msg, size_t msgsz)
{
    for (iComponent *C: mCmptList)
    {
        if (C != origin)
        {
            C->recvmsg(msg, msgsz);
        }
    }
}


template <typename T>
inline void vane::iContainer::sendmsg(iComponent *origin, const T &msg)
{
    sendmsg(origin, (const void*)msg, sizeof(T));
}


template <typename T>
inline void vane::iContainer::addComponent()
{
    static_assert(
        std::is_base_of_v<iComponent, T>,
        "T must be derivative of iComponent"
    );

    mCmptList.insert(
        static_cast<iComponent*>(new T(this))
    );
}