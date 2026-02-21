#include <vane/media_layer>
#include "vane/log.hpp"

extern void vaneEnableOpenGlDebugOutput();
extern GLuint vaneCreateFramebuffer();
extern GLuint vaneCompileScreenQuadProgram();
static GLuint screenquad_program_;

using namespace vane;


Window::Window(Platform *plat, const char *name, int width, int height)
:   IoDevice(plat)
{
    mSdlWin = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL);
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

    gl::GetIntegerv(GL_MAJOR_VERSION, &mGlVersionMajor);
    gl::GetIntegerv(GL_MINOR_VERSION, &mGlVersionMinor);
    VLOG_INFO("Context supports OpenGL {}.{}", mGlVersionMajor, mGlVersionMinor);
    VLOG_INFO("Created window {}", mSdlWinID);


    gl::CreateVertexArrays(1, &mVAO);
    screenquad_program_ = vaneCompileScreenQuadProgram();

    vaneEnableOpenGlDebugOutput();
    mFBO = vaneCreateFramebuffer();
}


Window::~Window()
{
    if (!SDL_GL_DestroyContext(mSdlGlCtx))
        VLOG_ERROR("Failure destroying SDL_GLContext");
    SDL_DestroyWindow(mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


void Window::onUpdate()
{
    SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);

    gl::BindVertexArray(mVAO);
    gl::UseProgram(screenquad_program_);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(mSdlWin);
}


void Window::onEvent(void *ptr)
{
    SDL_Event *e = (SDL_Event*)ptr;

    if (!SDL_GetWindowFromEvent(e))
        return;

    if (e->window.windowID != mSdlWinID)
        return;

    if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        mPlatform->freeIoDevice(this);

    if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
        mPlatform->freeIoDevice(this);
}

