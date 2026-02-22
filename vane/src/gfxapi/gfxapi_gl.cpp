#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


GfxApi *vane::gfxapi::getGfxApi()
{
    static GfxApiGl api;
    return static_cast<GfxApi*>(&api);
}


// Framebuffer &GfxApiGl::createFramebuffer()
// {
//     static FramebufferGl fb(*this);
//     return static_cast<Framebuffer&>(fb);
// }


// Texture &GfxApiGl::createTexture(int w, int h, const void *data)
// {
//     static TextureGl fb(*this, w, h, data);
//     return static_cast<Texture&>(fb);
// }


std::unique_ptr<Window> GfxApiGl::createWindow(const char *name, int w, int h)
{ return std::make_unique<WindowGl>(*this, name, w, h); }

std::unique_ptr<Framebuffer> GfxApiGl::createFramebuffer()
{ return std::make_unique<FramebufferGl>(*this); }

std::unique_ptr<Texture> GfxApiGl::createTexture(int w, int h, const void *data)
{ return std::make_unique<TextureGl>(*this, w, h, data); }

std::unique_ptr<ShaderProgram> GfxApiGl::createShaderProgram(const char *vertpath, const char *fragpath)
{ return std::make_unique<ShaderProgramGl>(*this, vertpath, fragpath); }

std::unique_ptr<ComputeProgram> GfxApiGl::createComputeProgram(const char *comppath)
{ return std::make_unique<ComputeProgramGl>(*this, comppath); }




// Framebuffer::Framebuffer(GfxApi &api)
// :   mId(0)
// {
//     gl::CreateFramebuffers(1, &mId);
//     // gl::NamedFramebufferTexture(mId, GL_COLOR_ATTACHMENT0, colorTex, 0);
//     // gl::NamedFramebufferTexture(mId, GL_DEPTH_ATTACHMENT, depthTex, 0);

//     if (gl::CheckNamedFramebufferStatus(mId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//     {
//         VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
//     }

// }


// Texture::Texture(GfxApi &api, int w, int h, const void *data)
// :   mApi(api)
// {
//     gl::CreateTextures(GL_TEXTURE_2D, 1, &mId);
//     gl::TextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
//     gl::TextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
//     gl::TextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     gl::TextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//     gl::TextureStorage2D(mId, 1, GL_RGBA8, w, h);
//     gl::TextureSubImage2D(mId, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

//     // gl::TextureStorage2D(mId, 1, GL_DEPTH_COMPONENT24, w, h);
//     // gl::TextureSubImage2D(mId, 0, 0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, data);

// }

