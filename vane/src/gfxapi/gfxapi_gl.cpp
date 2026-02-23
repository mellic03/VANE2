#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


GfxApi *vane::gfxapi::getGfxApi()
{
    static GfxApiGl api;
    return static_cast<GfxApi*>(&api);
}

GfxApiGl::GfxApiGl()
:   mBaseApi(static_cast<GfxApi&>(*this)),
    mMainWindow(createWindowGl("Main Window", 1024, 1024))
{

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

WindowPtr GfxApiGl::getMainWindow()
{
    return mMainWindow;
}



WindowGlPtr GfxApiGl::createWindowGl(const char *name, int w, int h)
{
    // return WindowTypeGl(new WindowGl(*this, name, w, h));
    mWindows.push_back(std::make_shared<WindowGl>(*this, name, w, h));
    return mWindows.back();
}

FramebufferGlPtr GfxApiGl::createFramebufferGl()
{
    // return FramebufferTypeGl(new FramebufferGl(*this));
    mFramebuffers.push_back(std::make_shared<FramebufferGl>(*this));
    return mFramebuffers.back();
}

TextureGlPtr GfxApiGl::createTextureGl(int w, int h, const void *data)
{
    // return TextureTypeGl(new TextureGl(*this, w, h, data));
    mTextures.push_back(std::make_shared<TextureGl>(*this, w, h, data));
    return mTextures.back();
}

ShaderProgramGlPtr GfxApiGl::createShaderProgramGl(const char *vertpath, const char *fragpath)
{
    // return ShaderProgramTypeGl(new ShaderProgramGl(*this, vertpath, fragpath));
    mShaderPrograms.push_back(std::make_shared<ShaderProgramGl>(*this, vertpath, fragpath));
    return mShaderPrograms.back();
}

ComputeProgramGlPtr GfxApiGl::createComputeProgramGl(const char *comppath)
{
    // return ComputeProgramTypeGl(new ComputeProgramGl(*this, comppath));
    mComputePrograms.push_back(std::make_shared<ComputeProgramGl>(*this, comppath));
    return mComputePrograms.back();
}



WindowPtr GfxApiGl::createWindow(const char *name, int w, int h)
{
    return createWindowGl(name, w, h);
}

FramebufferPtr GfxApiGl::createFramebuffer()
{
    return createFramebufferGl();
}

TexturePtr GfxApiGl::createTexture(int w, int h, const void *data)
{
    return createTextureGl(w, h, data);
}

ShaderProgramPtr GfxApiGl::createShaderProgram(const char *vertpath, const char *fragpath)
{
    return createShaderProgramGl(vertpath, fragpath);
}

ComputeProgramPtr GfxApiGl::createComputeProgram(const char *comppath)
{
    return createComputeProgramGl(comppath);
}




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

