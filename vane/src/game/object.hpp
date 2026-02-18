#pragma once

#include <glm/glm.hpp>


namespace vane
{
    class Object;
    class CharacterObject;
    // class PhysicsComponent;
    // class GraphicsComponent;
}



class vane::Object
{
public:
    glm::vec3 mPos, mVel, mAcc;
    virtual void update() {  };

private:

};


class vane::CharacterObject: public vane::Object
{
public:
    glm::vec3 mPos, mVel, mAcc;
    virtual void update() override;

private:

};


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
