#include <vane.hpp>
#include <filesystem>

using namespace vane;


// vane::Platform::Platform(IoApi &io, GfxApi &gfx)
// :   mIo(io), mGfx(gfx)
vane::Platform::Platform()
{
    std::filesystem::current_path(std::filesystem::path(SDL_GetBasePath()));

    setOpStat(OpState::Starting);
    VLOG_INFO("Initializing PlatformSDL3");

    // if (false == SDL_Init(SDL_INIT_VIDEO))
    //     VLOG_FATAL("{}", SDL_GetError());

    // if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
    //     VLOG_ERROR("{}", SDL_GetError());

    // if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
    //     VLOG_ERROR("{}", SDL_GetError());

    // if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5))
    //     VLOG_ERROR("{}", SDL_GetError());

    // if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
    //     VLOG_ERROR("{}", SDL_GetError());

    // if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24))
    //     VLOG_ERROR("{}", SDL_GetError());

    // if (!SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8))
    //     VLOG_ERROR("{}", SDL_GetError());

    setOpStat(OpState::Running);
    VLOG_INFO("Initialized PlatformSDL3");

}


bool vane::Platform::running()
{
    return mOpStat < OpState::Stopped;
}


void Platform::update()
{
    if (mServices.empty())
    {
        this->shutdown();
    }

    ServiceManager::update();
    // mOpStatTx.write(&mOpStat);
    // mOpAuthRx.read(&mOpAuth);
    // mOpStatTx.bind(mOpAuthRx);


    // SDL_Event e;
    // while (SDL_PollEvent(&e))
    // {
    //     if (e.type == SDL_EVENT_QUIT)
    //     {
    //         this->shutdown();
    //         return;
    //     }

    //     for (auto &obj: mServices)
    //     {
    //         obj->onEvent((void*)(&e));
    //     }
    // }
}


void vane::Platform::shutdown()
{
    setOpStat(OpState::Stopping);
    VLOG_INFO("Shutdown initiated");

    mServices.clear();

    setOpStat(OpState::Stopped);
    VLOG_INFO("Shutdown complete");
}


void Platform::setOpStat(OpState opstat)
{
    mOpStat = opstat;
    // mOpStatTx->write(&mOpStat);
}

