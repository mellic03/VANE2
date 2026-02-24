#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using namespace vane::gfxapi;

extern void vaneEnableOpenGlDebugOutput();


detail::RenderEngineBaseRaii::RenderEngineBaseRaii()
{
    if (false == SDL_Init(SDL_INIT_VIDEO))
        VLOG_FATAL("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8))
        VLOG_ERROR("{}", SDL_GetError());
}




struct UboCameraData
{
    glm::vec4 rgba = glm::vec4(0.5f);
    glm::mat4 T;
    glm::mat4 V;
    glm::mat4 P;
};


RenderEngine::RenderEngine(const char *name, int width, int height)
:   RenderEngineBaseRaii(),
    m_win(new Window(name, width, height)),
    m_winprg("data/shader/quad.vert", "data/shader/quad.frag")
{

}

static UboCameraData *camdata_ptr_ = nullptr;

void RenderEngine::onUpdate()
{
    static UboWrapperT<UboCameraData> ubo_camera_("ubo_CameraData");
    static UboCameraData &camdata_ = ubo_camera_.get();
    camdata_ptr_ = &camdata_;

    m_win->_makeCurrent();


    // SDL_GetMouseState()
    camdata_.T = glm::mat4(1.0f);
    camdata_.V = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camdata_.P = glm::perspective(glm::radians(80.0f), 1.0f, 0.001f, 100.0f);
    ubo_camera_.sendToGpu();
    ubo_camera_.bindToProgram(&m_winprg);

    gl::UseProgram(m_winprg.mId);
    gl::BindVertexArray(m_win->mVAO);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    m_win->_swap();

    // mServiceManager->getService<RenderEngine>
}


void RenderEngine::onShutdown()
{
    delete m_win;
}


void RenderEngine::onMsgRecv(srvmsg_t msg)
{
    printf("[RenderEngine::onMsgRecv] msg=%d\n", msg);

    switch (msg)
    {
        case GfxApiMsg::WIN_MAXIMIZE:
            break;
        case GfxApiMsg::WIN_MINIMIZE:
            break;
        default:
            return;
    }

}



int RenderEngine::onCmdRecv(int cmd, void *arg)
{
    // printf("[RenderEngine::onMsgRecv] msg=%d\n", msg);
    SDL_Event *e = (SDL_Event*)arg;


    switch (cmd)
    {
        case GfxApiMsg::WIN_EVENT:
        {
            if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
                srvMsgToAll(SrvMsg::SHUTDOWN);
            
            if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
                srvMsgToAll(SrvMsg::SHUTDOWN);

            return 0;
        }
        case GfxApiMsg::KEYDOWN_EVENT:
        {
            if (!camdata_ptr_)
                return 1;

            if (e->key.key == SDLK_A)
                camdata_ptr_->rgba.r *= 0.99f;

            if (e->key.key == SDLK_D)
                camdata_ptr_->rgba.r *= 1.01f;

            // if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            //     srvMsgToAll(SrvMsg::SHUTDOWN);
            
            // if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
            //     srvMsgToAll(SrvMsg::SHUTDOWN);

            return 0;
        }

        default:
            return 1;
    }

}












FramebufferPtr RenderEngine::createFramebuffer()
{
    return std::make_unique<Framebuffer>();
}

RenderProgramPtr RenderEngine::createRenderProgram(const char *vertpath, const char *fragpath)
{
    return std::make_unique<RenderProgram>(vertpath, fragpath);
}

ComputeProgramPtr RenderEngine::createComputeProgram(const char *filepath)
{
    return std::make_unique<ComputeProgram>(filepath);
}






void RenderEngine::drawToWindow(Window *win, RenderGraph &rg)
{
    
}

void RenderEngine::drawToFramebuffer(Framebuffer &fb, RenderGraph &rg)
{
    _drawFramebuffer(fb, rg.rootNode());
}

void RenderEngine::_drawFramebuffer(Framebuffer &fb, RenderNode *node)
{
    if (0) // culling condition
    {
        return;
    }

    for (auto *child: node->children)
    {
        _drawFramebuffer(fb, child);
    }
}





RenderEngine::Window *RenderEngine::createWindow(const char *name, int w, int h)
{
    return new Window(name, w, h);
}

