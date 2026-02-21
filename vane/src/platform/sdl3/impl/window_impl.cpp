// #include <SDL3/SDL.h>
// #include "vane/platform.hpp"
// #include "../gl_bindings.hpp"

// extern void vaneEnableOpenGlDebugOutput();
// extern GLuint vaneCreateFramebuffer();
// extern GLuint vaneCompileScreenQuadProgram();
// static GLuint screenquad_program_;

// using namespace vane;


// struct Window::Impl
// {
// public:
//     Impl(Window *win, const char *name, int w, int h);
//     ~Impl();
//     void onUpdate();
//     void onEvent(void*);

// private:
//     Platform     *mPlatform;
//     Window       *mWindow;

//     SDL_Window   *mSdlWin;
//     SDL_GLContext mSdlGlCtx;
//     SDL_WindowID  mSdlWinID;

//     int32_t mGlVersionMajor;
//     int32_t mGlVersionMinor;

//     // Should be seperated out
//     // --------------------------
//     uint32_t mFBO;
//     uint32_t mVAO;
//     // --------------------------
// };


// Window::Impl::Impl(Window *win, const char *name, int width, int height)
// :   mPlatform(win->mPlatform), mWindow(win)
// {
//     mSdlWin = SDL_CreateWindow(name, width, height, SDL_WINDOW_OPENGL);
//     if (mSdlWin == NULL)
//         VLOG_FATAL("SDL_CreateWindow: {}", SDL_GetError());
//     mSdlWinID = SDL_GetWindowID(mSdlWin);

//     mSdlGlCtx = SDL_GL_CreateContext(mSdlWin);
//     if (mSdlGlCtx == nullptr)
//         VLOG_FATAL("SDL_GL_CreateContext: {}", SDL_GetError());

//     if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
//         VLOG_FATAL("gladLoadGLLoader failure");

//     if (!SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx))
//         VLOG_ERROR("SDL_GL_MakeCurrent: {}", SDL_GetError());

//     gl::GetIntegerv(GL_MAJOR_VERSION, &mGlVersionMajor);
//     gl::GetIntegerv(GL_MINOR_VERSION, &mGlVersionMinor);
//     VLOG_INFO("Context supports OpenGL {}.{}", mGlVersionMajor, mGlVersionMinor);
//     VLOG_INFO("Created window {}", mSdlWinID);


//     gl::CreateVertexArrays(1, &mVAO);
//     screenquad_program_ = vaneCompileScreenQuadProgram();

//     vaneEnableOpenGlDebugOutput();
//     mFBO = vaneCreateFramebuffer();
// }


// Window::Impl::~Impl()
// {
//     if (!SDL_GL_DestroyContext(mSdlGlCtx))
//         VLOG_ERROR("Failure destroying SDL_GLContext");
//     SDL_DestroyWindow(mSdlWin);
//     VLOG_INFO("Destroyed window {}", mSdlWinID);
// }


// void Window::Impl::onUpdate()
// {
//     SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);

//     gl::BindVertexArray(mVAO);
//     gl::UseProgram(screenquad_program_);
//     gl::DrawArrays(GL_TRIANGLES, 0, 3);

//     SDL_GL_SwapWindow(mSdlWin);
// }


// void Window::ImplonEvent(void *ptr)
// {
//     SDL_Event *e = (SDL_Event*)ptr;

//     if (!SDL_GetWindowFromEvent(e))
//         return;

//     if (e->window.windowID != mSdlWinID)
//         return;

//     if (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
//         mPlatform->iodev_delete(mWindow);

//     if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
//         mPlatform->iodev_delete(mWindow);
// }



// vane::Window::Window(Platform *plat, const char *name, int w, int h)
// :   IoDevice(plat), m_impl(new Impl(this, name, w, h)) {  }
// vane::Window::~Window() {  }
// void vane::Window::onUpdate()  { m_impl->onUpdate(); }
// void vane::Window::onEvent(void *ptr) { m_impl->onEvent(ptr); }

