#include "platform_impl.hpp"
#include "gl_bindings.hpp"
#include "vane/log.hpp"

extern void vaneEnableOpenGlDebugOutput();
extern GLuint vaneCreateFramebuffer();
static GLuint test_fbo_;

using namespace vane;


gfxlib_gl::WindowImpl::WindowImpl(Platform *platform, const char *name, int x, int y, int w, int h)
:   mPlatform(platform)
{
    mSdlWin = SDL_CreateWindow(name, 1024, 1024, SDL_WINDOW_OPENGL);
    if (mSdlWin == NULL)
        VLOG_FATAL("{}", SDL_GetError());
    mSdlWinID = SDL_GetWindowID(mSdlWin);

    mSdlGlCtx = SDL_GL_CreateContext(mSdlWin);
    if (mSdlGlCtx == nullptr)
        VLOG_FATAL("{}", SDL_GetError());

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        VLOG_FATAL("gladLoadGLLoader failure");

    if (!SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetSwapInterval(0))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_SetWindowRelativeMouseMode(mSdlWin, false))
        VLOG_ERROR("{}", SDL_GetError());

    static bool is_first = true;
    if (is_first)
    {
        GLint major, minor;
        gl::GetIntegerv(GL_MAJOR_VERSION, &major);
        gl::GetIntegerv(GL_MINOR_VERSION, &minor);
        VLOG_INFO("Device supports up to OpenGL {}.{}", major, minor);
        is_first = false;
    }

    VLOG_INFO("Created window {}", mSdlWinID);

    vaneEnableOpenGlDebugOutput();
    test_fbo_ = vaneCreateFramebuffer();
}



gfxlib_gl::WindowImpl::~WindowImpl()
{
    if (!SDL_GL_DestroyContext(mSdlGlCtx))
    {
        VLOG_ERROR("Failure destroying SDL_GLContext");
    }

    SDL_DestroyWindow(mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


#include <glm/glm.hpp>
// extern uint32_t compute_shader_init();
void gfxlib_gl::WindowImpl::update()
{
    // static bool first = true;
    // static uint32_t prog = 0;
    // if (first)
    // {
    //     first = false;
    //     prog = compute_shader_init();
    // }
    // gl::UseProgram(prog);
    // gl::DispatchCompute(8, 8, 1);

    SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);

    // glm::vec4 rgba(0.5f, 1.0f, 0.25f, 1.0f);
    // glm::vec4 dpth(0.5f, 1.0f, 0.25f, 1.0f);
    // gl::BindFramebuffer(GL_FRAMEBUFFER, test_fbo_);
    // gl::ClearNamedFramebufferfv(test_fbo_, GL_COLOR, 0, &(rgba[0]));
    // gl::ClearNamedFramebufferfv(test_fbo_, GL_DEPTH, 0, &(dpth[0]));

    gl::ClearColor(0.5f, 0.75f, 0.25f, 1.0f);
    gl::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_GL_SwapWindow(mSdlWin);
}


void gfxlib_gl::WindowImpl::updateEvent(SDL_Event &e)
{
    if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    {
        mPlatform->destroyWindow_ptr(this);
    }

    else if (e.type == SDL_EVENT_KEY_UP)
    {
        if (e.key.key == SDLK_ESCAPE)
        {
            mPlatform->destroyWindow_ptr(this);
        }
    }
}
