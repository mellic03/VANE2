#pragma once
#include <glm/glm.hpp>

namespace vane
{
    class Transform;
}

class vane::Transform
{
public:
    Transform()
    {

    }

private:
    glm::vec3 mAcc;
    glm::vec3 mVel;
    glm::vec3 mPos;
};