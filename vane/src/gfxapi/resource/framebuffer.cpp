#include "gfxapi/gfxapi_gl.hpp"
#include "gfxapi/underlyingtype.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


FramebufferGl::FramebufferGl(GfxApiGl &api)
:   GfxResourceGl(api)
{
    gl::CreateFramebuffers(1, &mId);
    // gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, mOutTex->mId, 0);
    // gl::NamedFramebufferTexture(mId, GL_DEPTH_ATTACHMENT, depthTex, 0);

    // if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    // {
    //     VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    // }
}


FramebufferGl::~FramebufferGl()
{
    gl::DeleteFramebuffers(1, &mId);
}


void FramebufferGl::_check_status()
{
    if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    }
}


void FramebufferGl::setTextureDst(const std::shared_ptr<Texture> &tex)
{
    mOutTex = std::dynamic_pointer_cast<TextureGl>(tex);
    gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, mOutTex->mId, 0);
    _check_status();
}


