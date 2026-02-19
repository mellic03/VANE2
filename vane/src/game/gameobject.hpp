#pragma once

#include "interface/icomponent.hpp"
#include "vane/dsa/linkedlist.hpp"
#include "vane/transform.hpp"

#include <type_traits>


namespace vane
{
    class GameObject: public Transformable
    {
    private:
        dsa::LinkedList<iComponent> mComponents;

    public:
        GameObject() {  };

        void update();
        void sendmsg(iComponent *origin, const void *msg, size_t msgsz);

        template <typename T>
        void sendmsg(iComponent *origin, const T &msg);

        template <typename T>
        void addComponent();

    };
}

inline void vane::GameObject::update()
{
    for (iComponent *C: mComponents)
    {
        C->update();
    }
}


inline void vane::GameObject::sendmsg(iComponent *origin, const void *msg, size_t msgsz)
{
    for (iComponent *C: mComponents)
    {
        if (C != origin)
        {
            C->recvmsg(msg, msgsz);
        }
    }
}


template <typename T>
inline void vane::GameObject::sendmsg(iComponent *origin, const T &msg)
{
    sendmsg(origin, (const void*)msg, sizeof(T));
}


template <typename T>
inline void vane::GameObject::addComponent()
{
    static_assert(
        std::is_base_of_v<iComponent, T>,
        "T must be derivative of iComponent"
    );

    mComponents.insert(
        static_cast<iComponent*>(new T(this))
    );
}
