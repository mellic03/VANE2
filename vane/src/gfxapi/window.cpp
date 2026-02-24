#include "gfxapi/gfxapi_gl.hpp"

using namespace vane::gfxapi;


RenderEngine::Window::Window(const char *name, int width, int height)
{
    mSdlWin = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL);
    if (mSdlWin == NULL)
        VLOG_FATAL("SDL_CreateWindow: {}", SDL_GetError());

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
    VLOG_INFO("Context supports OpenGL {}.{}", GLVersion.major, GLVersion.minor);

    // SDL_HideWindow(mSdlWin);
    gl::CreateVertexArrays(1, &mVAO);

    // mFBO = vaneCreateFramebuffer();
    VLOG_INFO("Created window {}", mSdlWinID);
}


RenderEngine::Window::~Window()
{
    if (!SDL_GL_DestroyContext((SDL_GLContext)mSdlGlCtx))
        VLOG_ERROR("Failure destroying SDL_GLContext");
    SDL_DestroyWindow((SDL_Window*)mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


void RenderEngine::Window::onEvent(const SDL_Event &e)
{
    if (e.window.windowID != mSdlWinID)
        return;

    // if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    //     mPlatform->freeIoDevice(this);

    // if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
    //     mPlatform->freeIoDevice(this);
}


void RenderEngine::Window::_makeCurrent()
{
    VANE_ASSERT(
        true == SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx),
        "Failed to make SDL/GL context"
    );

    VANE_ASSERT(
        0 != gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress),
        "Failed to load GLAD"
    );
}


void RenderEngine::Window::_swap()
{
    SDL_GL_SwapWindow(mSdlWin);
}

