#pragma once

#include "vane/gfxapi/framebuffer.hpp"
#include "vane/gfxapi/shader.hpp"
#include "vane/gfxapi/texture.hpp"


namespace vane::gfxapi
{
    namespace detail
    {
        class RenderEngineBaseRaii;
    }
}



class vane::gfxapi::detail::RenderEngineBaseRaii
{
public:
    RenderEngineBaseRaii();

};



class vane::gfxapi::RenderEngine
:   public vane::gfxapi::detail::RenderEngineBaseRaii,
    public vane::Service
{
public:
    struct Window;

    RenderEngine(const char *name, int width, int height);
    virtual void onUpdate() final;
    virtual void onShutdown() final;
    virtual void onMsgRecv(srvmsg_t) final;
    virtual int  onCmdRecv(int, void*) final;

    FramebufferPtr createFramebuffer();
    RenderProgramPtr createRenderProgram(const char *vertpath, const char *fragpath);
    ComputeProgramPtr createComputeProgram(const char *filepath);

    void drawToWindow(Window*, RenderGraph&);
    void drawToFramebuffer(Framebuffer&, RenderGraph&);
    void _drawFramebuffer(Framebuffer&, RenderNode*);


private:
    struct ApiControl {
        void debugOutputEnable();
        void debugOutputDisable();
    } m_apictl;

    Window *m_win;
    RenderProgram m_winprg;

    using WindowPtr = std::unique_ptr<Window>;

    std::vector<WindowPtr>          m_windows;
    std::vector<FramebufferPtr>     m_framebuffers;
    std::vector<TexturePtr>         m_textures;
    std::vector<RenderProgramPtr>   m_render_programs;
    std::vector<ComputeProgramPtr>  m_compute_programs;

    Window *createWindow(const char *name, int w=512, int h=512);

};

