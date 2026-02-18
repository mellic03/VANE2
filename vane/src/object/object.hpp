#pragma once

#include <glm/glm.hpp>


namespace vane
{
    class PhysicsComponent;
    class GraphicsComponent;
    class Object;
}


class vane::PhysicsComponent
{
public:
    void update(Object &obj);

private:
    float mInvMass = 0.01f;
};


class vane::GraphicsComponent
{
public:
    void update(Object &obj);

private:
    int mModelId = 3;
};


class vane::Object
{
public:
    glm::vec3 mPos, mVel, mAcc;
    void update();

private:
    PhysicsComponent  mPhysics;
    GraphicsComponent mGraphics;
};




void vane::Object::update()
{
    mPhysics.update(*this);
    mGraphics.update(*this);
}


void vane::PhysicsComponent::update(vane::Object &obj)
{
    static constexpr glm::vec3 G(0.0f, -9.81f, 0.0f);

    obj.mAcc = G;
    obj.mVel += obj.mAcc;
    obj.mPos += obj.mVel;
}


void vane::GraphicsComponent::update(vane::Object &obj)
{
    
}