#include "gfxapi/gfxapi_gl.hpp"

using namespace vane::gfxapi;


void RenderNode::update(RenderEngine &gfx, void *arg)
{
    for (auto *child: mNodes)
    {
        child->update(gfx, arg);
    }
}

