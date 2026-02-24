#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


Framebuffer::Framebuffer(RenderEngine &api)
:   GfxResource(api)
{
    gl::CreateFramebuffers(1, &mId);
    // gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, mOutTex->mId, 0);
    // gl::NamedFramebufferTexture(mId, GL_DEPTH_ATTACHMENT, depthTex, 0);

    // if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    // {
    //     VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    // }
}


Framebuffer::~Framebuffer()
{
    gl::DeleteFramebuffers(1, &mId);
}


void Framebuffer::_check_status()
{
    if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    }
}


void Framebuffer::setTextureDst(const std::shared_ptr<Texture> &outTex)
{
    mOutTex = outTex;
    gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, mOutTex->mId, 0);
    _check_status();
}


