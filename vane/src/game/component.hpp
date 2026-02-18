#pragma once

#include <glm/glm.hpp>


namespace vane
{
    class Object;
    class PhysicsComponent;
    class GraphicsComponent;
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

