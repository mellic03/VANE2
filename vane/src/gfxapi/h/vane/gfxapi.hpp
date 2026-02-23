#pragma once

// #include <SDL3/SDL.h>
#include <memory>
#include <vector>


namespace vane::gfxapi
{
    using IdType = uint32_t;

    class GfxApi;
    class GfxResource;
    class Window;
    class Framebuffer;
    class Texture;
    class GpuProgram;
    class ShaderProgram;
    class ComputeProgram;

    using WindowPtr         = std::shared_ptr<Window>;
    using FramebufferPtr    = std::shared_ptr<Framebuffer>;
    using TexturePtr        = std::shared_ptr<Texture>;
    using ShaderProgramPtr  = std::shared_ptr<ShaderProgram>;
    using ComputeProgramPtr = std::shared_ptr<ComputeProgram>;


    enum class TextureFormat
    {
        RED_U8,
        RGB_U8,
        RGBA_U8,
        RGBA_U32,
        RGBA_F16,
        RGBA_F32
    };
}




class vane::gfxapi::GfxApi
{
private:
    friend class Window;
    friend class Framebuffer;
    // friend class Texture;
    // WindowPtr mMainWindow;

    std::vector<WindowPtr>         mWindows;
    std::vector<FramebufferPtr>    mFramebuffers;
    std::vector<TexturePtr>        mTextures;
    std::vector<ShaderProgramPtr>  mShaderPrograms;
    std::vector<ComputeProgramPtr> mComputePrograms;


public:
    GfxApi();

    // WindowPtr         createWindow(const char *name, int w, int h);
    // FramebufferPtr    createFramebuffer();
    // TexturePtr        createTexture(int w, int h, const void *data);
    // ShaderProgramPtr  createShaderProgram(const char *v, const char *f);
    // ComputeProgramPtr createComputeProgram(const char *c);

};


class vane::gfxapi::GfxResource
{
public:
    GfxApi &mApi;
    IdType mId;

    GfxResource(GfxApi &api, IdType id=0)
    :   mApi(api), mId(id) {  };

};



class vane::gfxapi::Window: public GfxResource
{
public:
    Window(GfxApi&, const char *name, int w, int h);
    ~Window();
    void onUpdate();
    void onEvent(void*);
    void setFramebuffer(const FramebufferPtr&);
    FramebufferPtr getFramebuffer();

    void setProgram(const ShaderProgramPtr&);
    // ShaderProgramPtr getProgram();

    void makeCurrent();

private:
    void   *mSdlWin; // SDL_Window
    void   *mSdlGlCtx; // SDL_GLContext
    IdType  mSdlWinID; // SDL_WindowID

    int32_t mGlVersionMajor;
    int32_t mGlVersionMinor;

    std::shared_ptr<Framebuffer>   mFramebuffer;
    std::shared_ptr<ShaderProgram> mQuadProgram;
    uint32_t mVAO;
};


class vane::gfxapi::Framebuffer: public GfxResource
{
    std::shared_ptr<Texture> mOutTex;
    void _check_status();

public:
    Framebuffer(GfxApi&);
    ~Framebuffer();
    void setTextureDst(const std::shared_ptr<Texture>&);

};


class vane::gfxapi::Texture: public GfxResource
{
private:
    TextureFormat mTextureFormat;

public:
    Texture(GfxApi&, int w, int h, const void *data);
    ~Texture();

    TextureFormat getTextureFormat();
    void setTextureFormat(TextureFormat);

};


class vane::gfxapi::GpuProgram: public GfxResource
{
public:
    struct Shader {
        GpuProgram &mProg;
        IdType     mId;
        bool       mOkay;
        Shader(GpuProgram &prog, IdType id, const char *filepath);
    };

    GpuProgram(GfxApi&);
    // GpuProgram(GfxApi &api): GfxResource(api, gl::CreateProgram()) {  }
};


class vane::gfxapi::ShaderProgram: public GpuProgram
{
public:
    GpuProgram::Shader mVert, mFrag;
    ShaderProgram(GfxApi&, const char *v, const char *f);
    ~ShaderProgram();
};


class vane::gfxapi::ComputeProgram: public GpuProgram
{
public:
    GpuProgram::Shader mComp;
    ComputeProgram(GfxApi&, const char *c);
};



