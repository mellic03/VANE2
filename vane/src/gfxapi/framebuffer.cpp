#include "vane/gfxapi_gl.hpp"
#include "vane/log.hpp"
#include "gfxapi/gl.hpp"

using namespace vane::gfxapi;


vane::gfxapi::Framebuffer::Framebuffer(GfxApi &api)
:   GfxResource(api)
{
    gl::CreateFramebuffers(1, &mId);
    // gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, colorTex, 0);
    // gl::NamedFramebufferTexture(mId, GL_DEPTH_ATTACHMENT, depthTex, 0);

    if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    }

}


void vane::gfxapi::Framebuffer::setTarget(const Texture &tex)
{
    tex.getTextureFormat();
}
