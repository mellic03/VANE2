#pragma once

#include "vane/gfxapi.hpp"
#include "gfxapi/gl.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <vector>


namespace vane::gfxapi
{
    class GfxApiGl;
    class GfxResourceGl;
    class WindowGlRaii;
    class WindowGl;
    class FramebufferGl;
    class TextureGl;
    class GpuProgramGl;
    class ShaderProgramGl;
    class ComputeProgramGl;

    using WindowGlPtr         = std::shared_ptr<WindowGl>;
    using FramebufferGlPtr    = std::shared_ptr<FramebufferGl>;
    using TextureGlPtr        = std::shared_ptr<TextureGl>;
    using ShaderProgramGlPtr  = std::shared_ptr<ShaderProgramGl>;
    using ComputeProgramGlPtr = std::shared_ptr<ComputeProgramGl>;
}




class vane::gfxapi::GfxApiGl: public gfxapi::GfxApi
{
private:

    GfxApi &mBaseApi;
    WindowGlPtr mMainWindow;

    std::vector<WindowGlPtr>         mWindows;
    std::vector<FramebufferGlPtr>    mFramebuffers;
    std::vector<TextureGlPtr>        mTextures;
    std::vector<ShaderProgramGlPtr>  mShaderPrograms;
    std::vector<ComputeProgramGlPtr> mComputePrograms;


public:
    GfxApiGl();

    virtual WindowPtr getMainWindow() final;

    WindowGlPtr         createWindowGl(const char *name, int w, int h);
    FramebufferGlPtr    createFramebufferGl();
    TextureGlPtr        createTextureGl(int w, int h, const void *data);
    ShaderProgramGlPtr  createShaderProgramGl(const char *v, const char *f);
    ComputeProgramGlPtr createComputeProgramGl(const char *c);

    virtual WindowPtr         createWindow(const char *name, int w, int h) final;
    virtual FramebufferPtr    createFramebuffer() final;
    virtual TexturePtr        createTexture(int w, int h, const void *data) final;
    virtual ShaderProgramPtr  createShaderProgram(const char *vpath, const char *fpath) final;
    virtual ComputeProgramPtr createComputeProgram(const char *cpath) final;

    template <typename T, typename... Args>
    std::unique_ptr<T> create(Args... args)
    {
        return std::unique_ptr<T>(new T(*this, args...));
    }

    // template <typename T, typename... Args>
    // std::shared_ptr<T> create_shared(Args... args)
    // { return std::create<T>(args...); }

};


class vane::gfxapi::GfxResourceGl
{
public:
    GfxApiGl &mApi;
    GLuint    mId;

    GfxResourceGl(GfxApiGl &api, GLuint id=0)
    :   mApi(api), mId(id) {  };

};



class vane::gfxapi::WindowGlRaii: public GfxResourceGl, public gfxapi::Window
{
public:
    WindowGlRaii(GfxApiGl&, const char *name, int w, int h);

protected:
    SDL_Window   *mSdlWin;
    SDL_GLContext mSdlGlCtx;
    SDL_WindowID  mSdlWinID;

    int32_t mGlVersionMajor;
    int32_t mGlVersionMinor;

};


class vane::gfxapi::WindowGl: public WindowGlRaii
{
    friend class GfxApiGl;
    friend class std::shared_ptr<FramebufferGl>;
    friend class std::unique_ptr<FramebufferGl>;

    std::shared_ptr<FramebufferGl>   mFramebuffer;
    std::shared_ptr<ShaderProgramGl> mQuadProgram;
    uint32_t mVAO;

public:
    WindowGl(GfxApiGl&, const char *name, int w, int h);
    virtual ~WindowGl();
    virtual void onUpdate() final;
    virtual void onEvent(void*) final;
    virtual void setFramebufferSrc(const std::shared_ptr<Framebuffer>&) final;
    void makeCurrent();
};


class vane::gfxapi::FramebufferGl: public GfxResourceGl, public Framebuffer
{
    std::shared_ptr<TextureGl> mOutTex;
    void _check_status();

public:
    FramebufferGl(GfxApiGl&);
    virtual ~FramebufferGl();

    void setTarget(const std::shared_ptr<TextureGl>&);
    virtual void setTextureDst(const std::shared_ptr<Texture>&) final;

};


class vane::gfxapi::TextureGl: public GfxResourceGl, public Texture
{
private:
    TextureFormat mTextureFormat;

public:
    TextureGl(GfxApiGl&, int w, int h, const void *data);
    virtual ~TextureGl();

    virtual TextureFormat getTextureFormat() final;
    virtual void setTextureFormat(TextureFormat) final;

};


class vane::gfxapi::GpuProgramGl: public GfxResourceGl
{
public:
    struct Shader {
        GpuProgramGl &mProg;
        GLuint       mId;
        bool         mOkay;
        Shader(GpuProgramGl &prog, GLuint id, const char *filepath);
    };

    GpuProgramGl(GfxApiGl &api): GfxResourceGl(api, gl::CreateProgram()) {  }
};


class vane::gfxapi::ShaderProgramGl: public GpuProgramGl, public ShaderProgram
{
public:
    GpuProgramGl::Shader mVert, mFrag;
    ShaderProgramGl(GfxApiGl&, const char *v, const char *f);
    virtual ~ShaderProgramGl();
};


class vane::gfxapi::ComputeProgramGl: public GpuProgramGl, public ComputeProgram
{
public:
    GpuProgramGl::Shader mComp;
    ComputeProgramGl(GfxApiGl&, const char *c);
};



