#pragma once

#include <cstddef>
#include <cstdint>
#include "vane/dsa/linkedlist.hpp"


namespace vane
{
    class GameObject;

    class iComponent
    {
    protected:
        friend class GameObject;
        GameObject *mObject;

    private:
        friend class dsa::LinkedList<iComponent>;
        iComponent *next_;

    public:
        iComponent(GameObject *obj): mObject(obj), next_(nullptr) {  }
        virtual ~iComponent() {  };
        virtual void update() = 0;
        virtual void recvmsg(const void *msg, size_t msgsz) = 0;
    };
}

