#include "gfxapi/gfxapi_gl.hpp"
#include "gfxapi/underlyingtype.hpp"
#include "vane/log.hpp"

extern void vaneEnableOpenGlDebugOutput();

using namespace vane::gfxapi;


WindowGlRaii::WindowGlRaii(GfxApiGl &api, const char *name, int width, int height)
:   GfxResourceGl(api)
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

    vaneEnableOpenGlDebugOutput();

    gl::GetIntegerv(GL_MAJOR_VERSION, &mGlVersionMajor);
    gl::GetIntegerv(GL_MINOR_VERSION, &mGlVersionMinor);
    VLOG_INFO("Context supports OpenGL {}.{}", mGlVersionMajor, mGlVersionMinor);
    VLOG_INFO("Created window {}", mSdlWinID);

}


WindowGl::WindowGl(GfxApiGl &api, const char *name, int width, int height)
:   WindowGlRaii(api, name, width, height),
    mFramebuffer(api.createFramebufferGl()),
    mQuadProgram(api.createShaderProgramGl("data/shader/quad.vert", "data/shader/quad.frag"))
{
    gl::CreateVertexArrays(1, &mVAO);
    
    // mFBO = vaneCreateFramebuffer();
}


WindowGl::~WindowGl()
{
    if (!SDL_GL_DestroyContext(mSdlGlCtx))
        VLOG_ERROR("Failure destroying SDL_GLContext");
    SDL_DestroyWindow(mSdlWin);
    VLOG_INFO("Destroyed window {}", mSdlWinID);
}


void WindowGl::onUpdate()
{
    SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);

    gl::BindVertexArray(mVAO);
    gl::UseProgram(mQuadProgram->mId);
    gl::DrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(mSdlWin);
}


void WindowGl::onEvent(void *ptr)
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


void WindowGl::setFramebufferSrc(const std::shared_ptr<Framebuffer> &fb)
{
    mFramebuffer = std::dynamic_pointer_cast<FramebufferGl>(fb);
}


void WindowGl::makeCurrent()
{

}
