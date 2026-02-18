#include "platform_impl.hpp"
#include "gl_bindings.hpp"
#include "vane/log.hpp"

using namespace vane;


gfxlib_gl::WindowImpl::WindowImpl(Platform *platform, const char *name, int x, int y, int w, int h)
:   mPlatform(platform)
{
    mSdlWin = SDL_CreateWindow(name, 1024, 1024, SDL_WINDOW_OPENGL);
    if (mSdlWin == NULL)
    {
        VLOG_FATAL("{}", SDL_GetError());
    }

    mSdlGlCtx = SDL_GL_CreateContext(mSdlWin);
    if (mSdlGlCtx == nullptr)
    {
        VLOG_FATAL("{}", SDL_GetError());
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        VLOG_FATAL("gladLoadGL error");
    }

    mSdlWinID = SDL_GetWindowID(mSdlWin);
    SDL_SetWindowPosition(mSdlWin, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

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


void gfxlib_gl::WindowImpl::update()
{
    SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);
    gl::ClearColor(1.0f, 0.5f, 0.0f, 1.0f);
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
