#include "component.hpp"
#include "object.hpp"


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

