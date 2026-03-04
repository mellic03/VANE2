#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "libidk/idk_random.hpp"

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




static SsboGpuOnly *ssbos_[2];
static void *camdata_ptr_ = nullptr;
static glm::vec3 camdata_pos_ = glm::vec3(0.0f);


RenderEngine::RenderEngine(const char *name, int width, int height)
:   RenderEngineBaseRaii(),
    m_win(new Window(name, width, height)),
    m_winprg("data/shader/screenquad.vert.spv", "data/shader/screenquad.frag.spv"),
    m_compute("data/shader/particles.comp.spv")
{
    m_compute_textures[0] = new Texture(1024, 1024, nullptr, TextureFormat::RGBA_F16);
    m_compute_textures[1] = new Texture(1024, 1024, nullptr, TextureFormat::RGBA_F16);


    ssbos_[0] = new SsboGpuOnly("SSBO_2", sizeof(gl_storage::ssbo_particles_t));
    ssbos_[1] = new SsboGpuOnly("SSBO_3", sizeof(gl_storage::ssbo_particles_t));

    auto *tmp = new gl_storage::ssbo_particles_t;
    for (int i=0; i<1024; i++)
    {
        idk::randvec3(0.0f, 1024.0f, &(tmp->pos[i][0]));
        idk::randvec3(-1.0f, +1.0f, &(tmp->vel[i][0]));
    }
    ssbos_[0]->write(0, sizeof(gl_storage::ssbo_particles_t), tmp);
    delete tmp;
}


void RenderEngine::onUpdate()
{
    m_win->_makeCurrent();

    gl::UseProgram(m_compute.mId);
    ssbos_[0]->bindToIndex(2);
    ssbos_[1]->bindToIndex(3);
    gl::DispatchCompute(gl_storage::SSBO_PARTICLE_COUNT/32, 1, 1);

    std::swap(m_compute_textures[0], m_compute_textures[1]);
    std::swap(ssbos_[0], ssbos_[1]);
    gl::MemoryBarrier(GL_ALL_BARRIER_BITS);


    gl::BindFramebuffer(GL_FRAMEBUFFER, 0);
    gl::UseProgram(m_winprg.mId);
    gl::BindTextureUnit(1, m_compute_textures[0]->mId);

    gl::BindVertexArray(m_win->mVAO);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    // gl::MultiDrawElementsIndirect(
    //     GL_TRIANGLES,
    //     GL_UNSIGNED_INT,
    //     (const void *)(sizeof(idk::gl::DrawCmd) * drawCmdOffset),
    //     drawCmdCount,
    //     sizeof(idk::gl::DrawCmd)
    // );

    m_win->_swap();
}



void RenderEngine::onMsgRecv(vane::message msg, void *arg)
{
    SDL_Event *e = (SDL_Event*)arg;

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

        case message::IO_KEYUP_EVENT:
            break;

        case message::IO_KEYDOWN_EVENT:
            if (camdata_ptr_)
            {
                // if (e->key.key == SDLK_A)  camdata_ptr_->rgba.r *= 0.99f;
                // if (e->key.key == SDLK_D)  camdata_ptr_->rgba.r *= 1.01f;

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
    (void)arg;

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








Camera *RenderEngine::createCamera(int w, int h)
{
    m_cameras.push_back(new Camera(w, h));
    return m_cameras.back();
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



struct UboCameraWriter: public UboWrapperT<gl_storage::ubo_camera_t>
{
    using UboWrapperT::UboWrapperT;
    static constexpr size_t BINDING_INDEX = 0;
};

void RenderEngine::drawToCamera(Camera &cam)
{
    static UboCameraWriter ubo_camera_("ubo_CameraData");
    auto &camubo = ubo_camera_.get();
    auto &tex = cam.mFramebuffer->mTexture;

    SDL_GetMouseState(&(camubo.mouse.x), &(camubo.mouse.y));
    camubo.mouse /= glm::vec4(tex->mWidth, tex->mHeight, 1.0f, 1.0f);
    camubo.mouse.y = 1.0f - camubo.mouse.y;

    camubo.T = cam.mTransform.to_mat4();
    camubo.V = cam.mView;
    camubo.P = cam.mProj;

    gl::BindFramebuffer(GL_FRAMEBUFFER, cam.mFramebuffer->mId);
    gl::UseProgram(m_winprg.mId);

    ubo_camera_.sendToGpu();
    ubo_camera_.bindToIndex(UboCameraWriter::BINDING_INDEX);

    gl::BindVertexArray(m_win->mVAO);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

}

void RenderEngine::drawToWindow(Window *win, RenderGraph &rg)
{
    (void)win;
    (void)rg;
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

