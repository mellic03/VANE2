#pragma once

#include <glm/glm.hpp>

namespace vane
{
    class GameObject;
    class Entity;

    class iComponent;
    class iHwIoComponent;

    // struct ComponentMessage
    // {
    //     int32_t type;
    //     int32_t subtype;
    //     void *data;
    
    //     static int32_t newMessageTypeID()
    //     {
    //         static int32_t value = 0;
    //         return value++;
    //     }
    // };
}


// class vane::iComponent
// {
// protected:
//     friend class vane::GameObject;
//     vane::GameObject *mObject;
//     vane::iComponent *mNext;

// public:
//     iComponent(GameObject *obj): mObject(obj), mNext(nullptr) {  }
//     virtual ~iComponent() {  };
//     virtual void update() = 0;
//     virtual void recvmsg(const void *msg, size_t msgsz) = 0;
// };



class vane::GameObject
{
public:
    glm::vec3 mAcc, mVel, mPos;

    GameObject();
    void update();
    void sendmsg(iComponent *origin, const void *msg, size_t msgsz);

    template <typename T>
    void sendmsg(iComponent *origin, const T &msg)
    {
        sendmsg(origin, (const void*)msg, sizeof(T));
    }

    template <typename T>
    inline void addComponent()
    {
        static_assert(
            std::is_base_of_v<iComponent, T>,
            "T must be derivative of iComponent"
        );

        auto *comp = static_cast<iComponent*>(new T(this));
        comp->mNext = mComponentList.head;
        mComponentList.head = comp;
    }

private:
    struct iComponentList
    {
        iComponent *head;

        struct iterator
        {
            iComponent *mC;

            iterator(iComponent *C): mC(C) {  };
            iterator(const iterator &I): mC(I.mC) {  };

            iterator &operator++() { mC = mC->mNext; return *this; };
            iterator operator++(int){ return iterator(mC->mNext); };

            bool operator == ( const iterator &rhs ) { return mC == rhs.mC; };
            bool operator != ( const iterator &rhs ) { return mC != rhs.mC; };
            iComponent *&operator*() { return mC; };
        };

        iterator begin() { return iterator(this->head); };
        iterator end()   { return iterator(nullptr); };
    };

    iComponentList mComponentList;
};



// class vane::CharacterObject: public vane::GameObject
// {
// public:
//     glm::vec3 mPos, mVel, mAcc;
//     virtual void update() override;

// private:

// };


// class vane::PhysicsComponent
// {
// public:
//     void update(Object &obj);

// private:
//     float mInvMass = 0.01f;
// };


// class vane::GraphicsComponent
// {
// public:
//     void update(Object &obj);

// private:
//     int mModelId = 3;
// };


// class vane::Object
// {
// public:
//     glm::vec3 mPos, mVel, mAcc;
//     virtual void update();

// private:
//     PhysicsComponent  mPhysics;
//     GraphicsComponent mGraphics;
// };
