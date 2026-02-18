#include <SDL3/SDL.h>

namespace vane
{
    class Platform;

    namespace gpu_gl
    {
        struct WindowImpl
        {
            static constexpr size_t MAX_WINDOWS = 8;
            static inline int32_t numWindows_ = 0;

            Platform     *mPlatform;
            SDL_Window   *mSdlWin;
            SDL_GLContext mSdlGlCtx;
            SDL_WindowID  mSdlWinID;

            WindowImpl(Platform*, const char *name, int x, int y, int w, int h);
            ~WindowImpl();
            void update();
            void updateEvent(SDL_Event&);
        };
    }
}


namespace vane
{
    using PlatformWindowType = gpu_gl::WindowImpl;
}

