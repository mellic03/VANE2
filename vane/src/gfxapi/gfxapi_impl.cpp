#include "vane/gfxapi_gl.hpp"
#include "vane/log.hpp"
#include "gfxapi/gl.hpp"

using namespace vane::gfxapi;


Framebuffer::Framebuffer(GfxApi &api)
:   mApi(api)
{
    gl::CreateFramebuffers(1, &mId);
    // gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, colorTex, 0);
    // gl::NamedFramebufferTexture(mId, GL_DEPTH_ATTACHMENT, depthTex, 0);

    if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    }

}


Texture::Texture(GfxApi &api, int w, int h, const void *data)
:   mApi(api)
{
    gl::CreateTextures(GL_TEXTURE_2D, 1, &mId);
    gl::TextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::TextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    gl::TextureStorage2D(mId, 1, GL_RGBA8, w, h);
    gl::TextureSubImage2D(mId, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // gl::TextureStorage2D(mId, 1, GL_DEPTH_COMPONENT24, w, h);
    // gl::TextureSubImage2D(mId, 0, 0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, data);

}

