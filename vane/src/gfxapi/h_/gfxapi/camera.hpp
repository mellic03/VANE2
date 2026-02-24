#pragma once

#include "vane/gfxapi.hpp"
#include "vane/transform.hpp"
#include <glm/glm.hpp>


struct vane::gfxapi::Camera
{
    friend class RenderEngine;
public:
    Camera();


private:
    Transform mTransform;

    struct {
        float pos[4];
        float rot[4];
        float scale;
    };

};

