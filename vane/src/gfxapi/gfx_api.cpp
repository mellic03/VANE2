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
    glm::vec4 mouse;
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
static glm::vec3 camdata_pos_ = glm::vec3(0.0f);

void RenderEngine::onUpdate()
{
    static UboWrapperT<UboCameraData> ubo_camera_("ubo_CameraData");
    static UboCameraData &camdata_ = ubo_camera_.get();
    camdata_ptr_ = &camdata_;

    m_win->_makeCurrent();

    SDL_GetMouseState(&(camdata_.mouse.x), &(camdata_.mouse.y));
    camdata_.mouse /= m_win->mSize;
    camdata_.mouse.y = 1.0f - camdata_.mouse.y;
    // camdata_.mouse += 

    camdata_.T = glm::translate(glm::mat4(1.0f), camdata_pos_);
    camdata_.V = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camdata_.P = glm::perspective(glm::radians(80.0f), 1.0f, 0.001f, 100.0f);
    ubo_camera_.sendToGpu();
    ubo_camera_.bindToProgram(&m_winprg);

    gl::UseProgram(m_winprg.mId);
    gl::BindVertexArray(m_win->mVAO);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    m_win->_swap();
}


// void RenderEngine::onShutdown()
// {
//     delete m_win;
// }


void RenderEngine::onMsgRecv(vane::message msg, void *arg)
{
    SDL_Event *e = (SDL_Event*)arg;

    // printf("[RenderEngine::onMsgRecv] msg=%d\n", msg);
    switch (msg)
    {
        case message::IO_WIN_EVENT:
        {
            SDL_Event *e = (SDL_Event*)arg;
            if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
                srvCmdToAll(command::SRV_SHUTDOWN, nullptr);
            if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
                srvCmdToAll(command::SRV_SHUTDOWN, nullptr);
            break;
        }

        case message::IO_KEYDOWN_EVENT:
            if (camdata_ptr_)
            {
                if (e->key.key == SDLK_A)  camdata_ptr_->rgba.r *= 0.99f;
                if (e->key.key == SDLK_D)  camdata_ptr_->rgba.r *= 1.01f;

                if (e->key.key == SDLK_LEFT)  camdata_pos_.x -= 0.0025f;
                if (e->key.key == SDLK_RIGHT) camdata_pos_.x += 0.0025f;

                if (e->key.key == SDLK_UP)    camdata_pos_.z += 0.0025f;
                if (e->key.key == SDLK_DOWN)  camdata_pos_.z -= 0.0025f;
            }
            break;

        default:
            break;
    }
}



void RenderEngine::onCmdRecv(vane::command cmd, void *arg)
{
    switch (cmd)
    {
        case command::GFX_ENABLE:
            break;

        case command::GFX_DISABLE:
            break;

        default:
            break;
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

