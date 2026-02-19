#include "platform.hpp"
#include "gl_bindings.hpp"
#include "vane/log.hpp"

extern void vaneEnableOpenGlDebugOutput();
extern GLuint vaneCreateFramebuffer();
extern GLuint vaneCompileScreenQuadProgram();
static GLuint screenquad_program_;

using namespace vane;


PlatformWindow::PlatformWindow(Platform *platform, const char *name, int x, int y, int w, int h)
:   mPlatform(platform)
{
    mSdlWin = SDL_CreateWindow(name, 1024, 1024, SDL_WINDOW_OPENGL);
    if (mSdlWin == NULL)
        VLOG_FATAL("SDL_CreateWindow: {}", SDL_GetError());
    mSdlWinID = SDL_GetWindowID(mSdlWin);

    mSdlGlCtx = SDL_GL_CreateContext(mSdlWin);
    if (mSdlGlCtx == nullptr)
        VLOG_FATAL("SDL_GL_CreateContext: {}", SDL_GetError());

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        VLOG_FATAL("gladLoadGLLoader failure");

    if (!SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx))
        VLOG_ERROR("SDL_GL_MakeCurrent: {}", SDL_GetError());

    gl::CreateVertexArrays(1, &mVAO);

    // if (!SDL_GL_SetSwapInterval(0))
    //     VLOG_ERROR("SDL_GL_SetSwapInterval: {}", SDL_GetError());

    // if (!SDL_SetWindowRelativeMouseMode(mSdlWin, false))
    //     VLOG_ERROR("SDL_SetWindowRelativeMouseMode: {}", SDL_GetError());

    static bool is_first = true;
    if (is_first)
    {
        is_first = false;
        GLint major, minor;
        gl::GetIntegerv(GL_MAJOR_VERSION, &major);
        gl::GetIntegerv(GL_MINOR_VERSION, &minor);
        VLOG_INFO("Device supports up to OpenGL {}.{}", major, minor);
        screenquad_program_ = vaneCompileScreenQuadProgram();
    }

    VLOG_INFO("Created window {}", mSdlWinID);

    vaneEnableOpenGlDebugOutput();
    mFBO = vaneCreateFramebuffer();
}


PlatformWindow::~PlatformWindow()
{
    if (!SDL_GL_DestroyContext(mSdlGlCtx))
    {
        VLOG_ERROR("Failure destroying SDL_GLContext");
    }

    SDL_DestroyWindow(mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


void PlatformWindow::update()
{
    SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);

    gl::BindVertexArray(mVAO);
    gl::UseProgram(screenquad_program_);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(mSdlWin);
}


void PlatformWindow::updateEvent(SDL_Event &e)
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
