#pragma once

#include <SDL3/SDL.h>
#include "vane/service.hpp"

namespace vane
{
    namespace gfxapi
    {
        class RenderEngine;
        class RenderGraph;
        class RenderNode;

        namespace detail
        {
            class RenderEngineBaseRaii;
        }
    }

    using GfxApi = gfxapi::RenderEngine;
}

#include "vane/gfxapi/framebuffer.hpp"
#include "vane/gfxapi/shader.hpp"
#include "vane/gfxapi/texture.hpp"



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
    virtual void onUpdate();
    virtual void onEvent(void*) {  };
    virtual void onMsgRecv(vane::message, void*) final;
    virtual void onCmdRecv(vane::command, void*) final;

    Camera *createCamera(int w, int h);
    FramebufferPtr createFramebuffer();
    RenderProgramPtr createRenderProgram(const char *vertpath, const char *fragpath);
    ComputeProgramPtr createComputeProgram(const char *filepath);

    void drawToCamera(Camera&);
    void drawToWindow(Window*, RenderGraph&);
    void drawToFramebuffer(Framebuffer&, RenderGraph&);
    void _drawFramebuffer(Framebuffer&, RenderNode*);


private:
    struct ApiControl {
        void debugOutputEnable();
        void debugOutputDisable();
    } m_apictl;

    using WindowPtr = std::unique_ptr<Window>;

    WindowPtr m_win;
    RenderProgram m_winprg;
    ComputeProgram m_compute;
    Texture *m_compute_textures[2];

    std::vector<WindowPtr>          m_windows;
    std::vector<Camera*>            m_cameras;
    std::vector<FramebufferPtr>     m_framebuffers;
    std::vector<TexturePtr>         m_textures;
    std::vector<RenderProgramPtr>   m_render_programs;
    std::vector<ComputeProgramPtr>  m_compute_programs;

    Window *createWindow(const char *name, int w=512, int h=512);

};

