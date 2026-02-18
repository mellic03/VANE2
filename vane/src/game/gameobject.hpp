#pragma once

#include <glm/glm.hpp>

namespace vane
{
    class GameObject;
    class iComponent;

    struct ComponentMessage
    {
        int32_t type;
        int32_t subtype;
        void *data;
    
        static int32_t newMessageTypeID()
        {
            static int32_t value = 0;
            return value++;
        }
    };
}


class vane::iComponent
{
protected:
    friend class vane::GameObject;
    vane::GameObject *mObject;
    vane::iComponent *mNext;

public:
    iComponent(GameObject *obj): mObject(obj), mNext(nullptr) {  }
    virtual ~iComponent() {  };
    virtual void update() = 0;
    virtual void recvmsg(const ComponentMessage &msg) = 0;

};


class vane::GameObject
{
private:
    iComponent *mCompHead;

public:
    glm::vec3 mAcc, mVel, mPos;

    GameObject();
    void update();

    template <typename T>
    inline void addComponent()
    {
        auto *comp = new T(this);
        comp->mNext = mCompHead;
        mCompHead = comp;
    }

    void sendmsg(iComponent *origin, const ComponentMessage &msg);

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
