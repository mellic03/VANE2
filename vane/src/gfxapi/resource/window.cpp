#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"

extern void vaneEnableOpenGlDebugOutput();

using namespace vane::gfxapi;


Window::Window(GfxApi &api, const char *name, int width, int height)
:   GfxResource(api)
{
    SDL_Window *sdlWin;
    SDL_GLContext sdlGlCtx;

    sdlWin = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL);
    if (sdlWin == NULL)
        VLOG_FATAL("SDL_CreateWindow: {}", SDL_GetError());

    sdlGlCtx = SDL_GL_CreateContext(sdlWin);
    if (sdlGlCtx == nullptr)
        VLOG_FATAL("SDL_GL_CreateContext: {}", SDL_GetError());

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        VLOG_FATAL("gladLoadGLLoader failure");

    if (!SDL_GL_MakeCurrent(sdlWin, sdlGlCtx))
        VLOG_ERROR("SDL_GL_MakeCurrent: {}", SDL_GetError());

    gl::GetIntegerv(GL_MAJOR_VERSION, &mGlVersionMajor);
    gl::GetIntegerv(GL_MINOR_VERSION, &mGlVersionMinor);

    VLOG_INFO("Context supports OpenGL {}.{}", mGlVersionMajor, mGlVersionMinor);
    VLOG_INFO("Context supports OpenGL {}.{}", GLVersion.major, GLVersion.minor);

    vaneEnableOpenGlDebugOutput();
    // SDL_HideWindow(sdlWin);
    
    mSdlWin   = (void*)sdlWin;
    mSdlGlCtx = (void*)sdlGlCtx;
    mSdlWinID = SDL_GetWindowID(sdlWin);

    gl::CreateVertexArrays(1, &mVAO);

    // mFBO = vaneCreateFramebuffer();
    VLOG_INFO("Created window {}", mSdlWinID);

    mApi.mWindows.push_back(std::shared_ptr<Window>(this));
}


Window::~Window()
{
    if (!SDL_GL_DestroyContext((SDL_GLContext)mSdlGlCtx))
        VLOG_ERROR("Failure destroying SDL_GLContext");
    SDL_DestroyWindow((SDL_Window*)mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


void Window::onUpdate()
{
    SDL_GL_MakeCurrent((SDL_Window*)mSdlWin, (SDL_GLContext)mSdlGlCtx);

    gl::BindVertexArray(mVAO);
    gl::UseProgram(mQuadProgram->mId);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow((SDL_Window*)mSdlWin);
}


void Window::onEvent(void *ptr)
{
    SDL_Event *e = (SDL_Event*)ptr;

    if (!SDL_GetWindowFromEvent(e))
        return;

    if (e->window.windowID != mSdlWinID)
        return;

    // if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    //     mPlatform->freeIoDevice(this);

    // if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
        // mPlatform->freeIoDevice(this);
}

void Window_onEventCallback(void *obj, void *arg)
{
    using namespace vane;

    auto *w = (gfxapi::Window*)obj;
    auto *e = (SDL_Event*)arg;

    if (!SDL_GetWindowFromEvent(e))
        return;

    if (e->window.windowID != w->mSdlWinID)
        return;

    // if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
    //     mPlatform->freeIoDevice(this);

    // if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
        // mPlatform->freeIoDevice(this);
}


void Window::setFramebuffer(const FramebufferPtr &fb)
{
    mFramebuffer = fb;
}

FramebufferPtr Window::getFramebuffer()
{
    return mFramebuffer;
}

void Window::setProgram(const ShaderProgramPtr &prog)
{
    mQuadProgram = prog;
}


void Window::makeCurrent()
{

}
