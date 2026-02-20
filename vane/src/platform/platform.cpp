#include "vane/platform/platform_SDL3.hpp"
// #include "gl_bindings.hpp"
// #include "vane/log.hpp"
#include <filesystem>


vane::OpState PlatformSDL3_init()
{
    using namespace vane;

    std::filesystem::current_path(std::filesystem::path(SDL_GetBasePath()));

    if (false == SDL_Init(SDL_INIT_VIDEO))
    {
        VLOG_FATAL("{}", SDL_GetError());
        return OpState::Invalid;
    }

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

    VLOG_INFO("SDL3 Initialized");

    return OpState::Running;
}


bool PlatformSDL3_poll(vane::Platform &plat, vane::PlatformEventType *e)
{
    if (SDL_PollEvent(e))
    {
        if (e->type == SDL_EVENT_QUIT)
        {
            plat.shutdown();
        }

        return true;
    }

    return false;
}



// bool vane::Platform::running()
// {
//     return mRunning;
// }


// void vane::Platform::shutdown()
// {
//     VLOG_INFO("Shutdown initiated");

//     for (auto *winptr: mWindows)
//         delete winptr;
//     mWindows.clear();

//     mRunning = false;

//     VLOG_INFO("Shutdown complete");
// }


// void vane::Platform::update()
// {
//     if (mWindows.empty())
//     {
//         this->shutdown();
//         return;
//     }

//     for (auto *winptr: cull_set_)
//     {
//         mWindows.erase(winptr);
//         delete winptr;
//     }
//     cull_set_.clear();

//     for (auto *winptr: mWindows)
//         winptr->update();

//     for (auto *iodev: mIoDevices)
//         iodev->update();

//     SDL_Event e;
//     while (SDL_PollEvent(&e))
//     {
//         if (e.type == SDL_EVENT_QUIT)
//         {
//             this->shutdown();
//             break;
//         }

//         if (!SDL_GetWindowFromEvent(&e))
//             continue;

//         if (auto *winptr = getWindow(e.window.windowID))
//             winptr->updateEvent(e);

//         for (auto *iodev: mIoDevices)
//             iodev->updateEvent(e);
//     }
// }


// vaneid_t vane::Platform::createWindow(const char *name, int w, int h)
// {
//     auto *win = new PlatformWindow(
//         this, name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h
//     );
//     mWindows.insert(win);
//     return win->mSdlWinID;
// }


// vane::VaneStat vane::Platform::destroyWindow(vaneid_t sdlWinId)
// {
//     for (auto *winptr: mWindows)
//         if (winptr->mSdlWinID == sdlWinId)
//             return destroyWindow_ptr(winptr);
//     VLOG_ERROR("Deletion of non-existent window ({})", (uint32_t)sdlWinId);
//     return VaneStat::INVALID;
// }


// vane::VaneStat vane::Platform::destroyWindow_ptr(PlatformWindow *winptr)
// {
//     if (mWindows.contains(winptr))
//     {
//         cull_set_.insert(winptr);
//         return VaneStat::OK;
//     }

//     VLOG_ERROR("Deletion of non-existent window ({})", winptr->mSdlWinID);
//     return VaneStat::INVALID;
// }


// vane::PlatformWindow *vane::Platform::getWindow(vaneid_t sdlWinId)
// {
//     for (auto *win: mWindows)
//         if (win->mSdlWinID == sdlWinId)
//             return win;
//     VLOG_WARN("Access of non-existent window ({})", sdlWinId);
//     return nullptr;
// }













// extern void vaneEnableOpenGlDebugOutput();
// extern GLuint vaneCreateFramebuffer();
// extern GLuint vaneCompileScreenQuadProgram();
// static GLuint screenquad_program_;

// using namespace vane;


// PlatformWindow::PlatformWindow(Platform *platform, const char *name, int x, int y, int w, int h)
// :   mPlatform(platform)
// {
//     mSdlWin = SDL_CreateWindow(name, 1024, 1024, SDL_WINDOW_OPENGL);
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

//     gl::CreateVertexArrays(1, &mVAO);

//     // if (!SDL_GL_SetSwapInterval(0))
//     //     VLOG_ERROR("SDL_GL_SetSwapInterval: {}", SDL_GetError());

//     // if (!SDL_SetWindowRelativeMouseMode(mSdlWin, false))
//     //     VLOG_ERROR("SDL_SetWindowRelativeMouseMode: {}", SDL_GetError());

//     static bool is_first = true;
//     if (is_first)
//     {
//         is_first = false;
//         GLint major, minor;
//         gl::GetIntegerv(GL_MAJOR_VERSION, &major);
//         gl::GetIntegerv(GL_MINOR_VERSION, &minor);
//         VLOG_INFO("Device supports up to OpenGL {}.{}", major, minor);
//         screenquad_program_ = vaneCompileScreenQuadProgram();
//     }

//     VLOG_INFO("Created window {}", mSdlWinID);

//     vaneEnableOpenGlDebugOutput();
//     mFBO = vaneCreateFramebuffer();
// }


// PlatformWindow::~PlatformWindow()
// {
//     if (!SDL_GL_DestroyContext(mSdlGlCtx))
//     {
//         VLOG_ERROR("Failure destroying SDL_GLContext");
//     }

//     SDL_DestroyWindow(mSdlWin);
//     VLOG_INFO("Destroyed window {}", mSdlWinID);
// }


// void PlatformWindow::update()
// {
//     SDL_GL_MakeCurrent(mSdlWin, mSdlGlCtx);

//     gl::BindVertexArray(mVAO);
//     gl::UseProgram(screenquad_program_);
//     gl::DrawArrays(GL_TRIANGLES, 0, 3);

//     SDL_GL_SwapWindow(mSdlWin);
// }


// void PlatformWindow::updateEvent(SDL_Event &e)
// {
//     if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
//     {
//         mPlatform->destroyWindow_ptr(this);
//     }

//     else if (e.type == SDL_EVENT_KEY_UP)
//     {
//         if (e.key.key == SDLK_ESCAPE)
//         {
//             mPlatform->destroyWindow_ptr(this);
//         }
//     }
// }
