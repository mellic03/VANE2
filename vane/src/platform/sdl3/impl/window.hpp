#include "vane/platform.hpp"
#include <SDL3/SDL.h>


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

