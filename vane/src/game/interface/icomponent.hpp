#pragma once

#include <cstddef>
#include <cstdint>


// namespace vane
// {
//     class GameObject;
//     class Container;

//     class iComponent
//     {
//     protected:
//         friend class GameObject;
//         GameObject *mObject;
//         iComponent *mNext;

//     public:
//         iComponent(GameObject *obj): mObject(obj), mNext(nullptr) {  }
//         virtual ~iComponent() {  };
//         virtual void update() = 0;
//         virtual void recvmsg(const void *msg, size_t msgsz) = 0;
//     };
// }


namespace vane
{
    class Container;

    class iComponent
    {
    protected:
        friend class Container;
        Container *mContainer;
        iComponent *mNext;

    public:
        iComponent(Container *C): mContainer(C), mNext(nullptr) {  }
        virtual ~iComponent() {  };
        virtual void update() = 0;
        virtual void recvmsg(const void *msg, size_t msgsz) = 0;
    };
}

