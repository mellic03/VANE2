#pragma once

#include <cstddef>
#include <cstdint>

namespace vane
{
    class GameObject;

    class iComponent
    {
    protected:
        friend class GameObject;
        GameObject *mObject;

    public:
        iComponent *mNext;

        iComponent(GameObject *obj): mObject(obj), mNext(nullptr) {  }
        virtual ~iComponent() {  };
        virtual void update() = 0;
        virtual void recvmsg(const void *msg, size_t msgsz) = 0;
    };
}

