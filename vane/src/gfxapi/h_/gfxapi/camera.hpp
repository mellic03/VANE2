#pragma once

#include "vane/gfxapi.hpp"
#include "vane/transform.hpp"
#include <glm/glm.hpp>


struct vane::gfxapi::Camera
{
    friend class RenderEngine;
private:
    FramebufferPtr mFramebuffer;

    glm::mat4 mProj;
    glm::mat4 mView;
    Transform mTransform;

public:
    Camera(int w, int h);

    Transform &getTransform() { return mTransform; }

};

