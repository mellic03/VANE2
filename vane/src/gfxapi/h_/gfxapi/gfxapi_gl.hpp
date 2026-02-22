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
    class WindowGl;
    class FramebufferGl;
    class TextureGl;
    class GpuProgramGl;
    class ShaderProgramGl;
    class ComputeProgramGl;
}




class vane::gfxapi::GfxApiGl: public gfxapi::GfxApi
{
private:
    GfxApi &mBaseApi;
    std::vector<std::unique_ptr<WindowGl>>         mWindows;
    std::vector<std::unique_ptr<FramebufferGl>>    mFramebuffers;
    std::vector<std::unique_ptr<TextureGl>>        mTextures;
    std::vector<std::unique_ptr<GpuProgramGl>>     mGpuPrograms;
    std::vector<std::unique_ptr<ShaderProgramGl>>  mShaderPrograms;
    std::vector<std::unique_ptr<ComputeProgramGl>> mComputePrograms;

public:
    GfxApiGl(): mBaseApi(static_cast<GfxApi&>(*this)) {  };

    virtual std::unique_ptr<Window> createWindow(const char *name, int w, int h) final;
    virtual std::unique_ptr<Framebuffer> createFramebuffer() final;
    virtual std::unique_ptr<Texture> createTexture(int w, int h, const void *data) final;
    virtual std::unique_ptr<ShaderProgram> createShaderProgram(const char *v, const char *f) final;
    virtual std::unique_ptr<ComputeProgram> createComputeProgram(const char *c) final;


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




class vane::gfxapi::WindowGl: public GfxResourceGl, public gfxapi::Window
{
    friend class GfxApiGl;
    friend class std::shared_ptr<FramebufferGl>;
    friend class std::unique_ptr<FramebufferGl>;

public:
    WindowGl(GfxApiGl&, const char *name, int w, int h);
    virtual ~WindowGl();
    virtual void setFramebufferSrc(const std::shared_ptr<Framebuffer>&) final;


    void onUpdate();
    void onEvent(void*);

private:
    SDL_Window   *mSdlWin;
    SDL_GLContext mSdlGlCtx;
    SDL_WindowID  mSdlWinID;

    int32_t mGlVersionMajor;
    int32_t mGlVersionMinor;

    // Should be seperated out
    // --------------------------
    std::unique_ptr<FramebufferGl> mFramebuffer;
    std::unique_ptr<ShaderProgramGl> mQuadProgram;
    uint32_t mVAO;
    // --------------------------

};


class vane::gfxapi::FramebufferGl: public GfxResourceGl, public Framebuffer
{
    std::shared_ptr<TextureGl> mOutTex;

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
};


class vane::gfxapi::ComputeProgramGl: public GpuProgramGl, public ComputeProgram
{
public:
    GpuProgramGl::Shader mComp;
    ComputeProgramGl(GfxApiGl&, const char *c);
};



