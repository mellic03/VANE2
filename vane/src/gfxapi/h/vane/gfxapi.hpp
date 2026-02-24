#pragma once

// #include <SDL3/SDL.h>
#include "vane/objmanager.hpp"
#include "vane/inplace_set.hpp"
#include <memory>
#include <vector>


namespace vane::gfxapi
{
    using IdType = uint32_t;

    class RenderEngine;
    class RenderGraph;
    
    class GfxResource;
    class Framebuffer;
    class Texture;
    class GpuProgram;
    class RenderProgram;
    class ComputeProgram;

    using FramebufferPtr    = std::shared_ptr<Framebuffer>;
    using TexturePtr        = std::shared_ptr<Texture>;
    using RenderProgramPtr  = std::shared_ptr<RenderProgram>;
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


class vane::gfxapi::RenderEngine: public vane::ObjectManager::Object
{
public:
    struct Window;

    RenderEngine(const char *name, int width, int height);
    virtual void onUpdate() final;

    RenderProgramPtr createRenderProgram(const char *vertpath, const char *fragpath);
    ComputeProgramPtr createComputeProgram(const char *filepath);

    void drawWindow(Window*, Framebuffer&);
    void drawFramebuffer(Framebuffer&, RenderGraph&);
    void _drawFramebuffer(Framebuffer&, RenderNode*);


private:
    struct ApiControl {
        void debugOutputEnable();
        void debugOutputDisable();
    } m_apictl;
    Window *m_win;

    using WindowPtr = std::unique_ptr<Window>;

    std::vector<WindowPtr>          m_windows;
    std::vector<FramebufferPtr>     m_framebuffers;
    std::vector<TexturePtr>         m_textures;
    std::vector<RenderProgramPtr>   m_render_programs;
    std::vector<ComputeProgramPtr>  m_compute_programs;

    Window *createWindow(const char *name, int w=512, int h=512);
};




class vane::gfxapi::GfxResource
{
public:
    RenderEngine &mApi;
    IdType mId;

    GfxResource(RenderEngine &api, IdType id=0)
    :   mApi(api), mId(id) {  };

};





class vane::gfxapi::Framebuffer: public GfxResource
{
    std::shared_ptr<Texture> mOutTex;
    void _check_status();

public:
    Framebuffer(RenderEngine&);
    ~Framebuffer();
    void setTextureDst(const std::shared_ptr<Texture>&);

};


class vane::gfxapi::Texture: public GfxResource
{
private:
    TextureFormat mTextureFormat;

public:
    Texture(RenderEngine&, int w, int h, const void *data);
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

    GpuProgram(RenderEngine&);
    // GpuProgram(RenderEngine &api): GfxResource(api, gl::CreateProgram()) {  }
};


class vane::gfxapi::RenderProgram: public GpuProgram
{
public:
    GpuProgram::Shader mVert, mFrag;
    RenderProgram(RenderEngine&, const char *v, const char *f);
    ~RenderProgram();
};


class vane::gfxapi::ComputeProgram: public GpuProgram
{
public:
    GpuProgram::Shader mComp;
    ComputeProgram(RenderEngine&, const char *c);
};



