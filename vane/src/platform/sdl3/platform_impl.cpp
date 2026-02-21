

#include "vane/detail/platform.hpp"
#include "vane/sample_port.hpp"
#include <SDL3/SDL.h>
#include "gl_bindings.hpp"
#include <filesystem>

using namespace vane;


struct vane::Platform::Impl
{
public:
    void init();
    void update();
    void shutdown();
    void killIoDevices();
    void flushIoDevices();
    void setOpStat(OpState);

private:
    friend class vane::Platform;
    RxSamplePort<OpCtrl>  *mOpAuthRx;
    TxSamplePort<OpState> *mOpStatTx;
    OpCtrl                 mOpAuth;
    OpState                mOpStat;
    std::vector<std::unique_ptr<IoDevice>> mIoDevices;

};

void Platform::Impl::init()
{
    std::filesystem::current_path(std::filesystem::path(SDL_GetBasePath()));

    setOpStat(OpState::Starting);
    VLOG_INFO("Initializing PlatformSDL3");

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

    setOpStat(OpState::Running);
    VLOG_INFO("Initialized PlatformSDL3");
}

void Platform::Impl::setOpStat(OpState opstat)
{
    mOpStat = opstat;
    mOpStatTx->write(&mOpStat);
}

void Platform::Impl::update()
{
    // mOpStatTx.write(&mOpStat);
    // mOpAuthRx.read(&mOpAuth);
    // mOpStatTx.bind(mOpAuthRx);

    if (mIoDevices.empty())
    {
        this->shutdown();
        return;
    }

    for (auto &iodev: mIoDevices)
    {
        iodev->onUpdate();
    }

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            this->shutdown();
            return;
        }

        for (auto &iodev: mIoDevices)
        {
            iodev->onEvent((void*)(&e));
        }
    }

    flushIoDevices();
}

void Platform::Impl::killIoDevices()
{
    for (auto &iodev: mIoDevices)
    {
        iodev->kill_ = true;
    }
}

void Platform::Impl::flushIoDevices()
{
    for (int i=mIoDevices.size()-1; i>=0; i--)
    {
        if (mIoDevices[i]->kill_)
        {
            std::swap(mIoDevices[i], mIoDevices.back());
            mIoDevices.pop_back();
        }
    }
}





vane::Platform::Platform()
:   m_impl(new Platform::Impl)
{
    // m_impl->mOpStatTx = new TxSamplePort<OpState>();
    // m_impl->mOpAuthRx = new RxSamplePort<OpCtrl>();
    m_impl->init();
}

void vane::Platform::update()
{
    m_impl->update();
}

bool vane::Platform::active()
{
    return m_impl->mOpStat < OpState::Stopped;
}

void vane::Platform::shutdown()
{
    m_impl->setOpStat(OpState::Stopping);
    VLOG_INFO("Shutdown initiated");

    m_impl->killIoDevices();
    m_impl->flushIoDevices();
    m_impl->setOpStat(OpState::Stopped);
    VLOG_INFO("Shutdown complete");
}

void vane::Platform::_addIoDevice(IoDevice *iodev)
{
    m_impl->mIoDevices.push_back(std::unique_ptr<IoDevice>(iodev));
}
























extern void vaneEnableOpenGlDebugOutput();
extern GLuint vaneCreateFramebuffer();
extern GLuint vaneCompileScreenQuadProgram();
static GLuint screenquad_program_;

using namespace vane;


class vane::Window: public vane::IoDevice
{
public:
    Window(vane::Platform*, const char *name, int w, int h);
    virtual ~Window();
    virtual void onUpdate() final;
    virtual void onEvent(void*) final;

private:
    SDL_Window   *mSdlWin;
    SDL_GLContext mSdlGlCtx;
    SDL_WindowID  mSdlWinID;

    int32_t mGlVersionMajor;
    int32_t mGlVersionMinor;

    // Should be seperated out
    // --------------------------
    uint32_t mFBO;
    uint32_t mVAO;
    // --------------------------

};




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
        mPlatform->iodev_delete(this);

    if ((e->type == SDL_EVENT_KEY_UP) && (e->key.key == SDLK_ESCAPE))
        mPlatform->iodev_delete(this);
}

