#pragma once

#include "vane/log.hpp"
#include "vane/time.hpp"
#include "vane/type.hpp"
#include "vane/util/funcptr.hpp"
#include "vane/rxSamplePort.hpp"
#include <vector>
#include <set>


namespace vane
{
    class Platform;

    enum class OpControl: uint8_t
    {
        None       = 0,
        Initialize = 1,
        Terminate  = 2
    };

    enum class OpState: uint8_t
    {
        Invalid  = 0,
        Starting,
        Running,
        Stopping,
        Stopped
    };
}


class vane::Platform
{
public:
    struct Impl
    {
        OpState (*init)(void);
        bool (*poll)(Platform&, PlatformEventType*);
    };

    class IoDevice
    {
    protected:
        vane::Platform *mPlatform;
    private:
        friend class vane::Platform;
        time::PeriodicTimer timer_;
        vaneid_t typeid_;
        bool     kill_;

    public:
        IoDevice(Platform *p)
        :   mPlatform(p), timer_(time::NsTime(0)) {  }

        virtual ~IoDevice() {  }
        virtual void onUpdate() = 0;
        virtual void onEvent(const PlatformEventType&) = 0;
    };


    Platform(const Platform::Impl&, TxMsgEndpoint&);

    bool active();
    void shutdown();
    void update();

    template <typename IoDevType, typename... Args>
    IoDevType *iodev_create(Args... args);
    VaneStat   iodev_delete(IoDevice *iodev);

private:
    struct ThisState {
        static constexpr int ALIVE = 2;
        static constexpr int DYING = 1;
        static constexpr int DEAD  = 0;
    };

    Platform::Impl      m_impl;
    OpState             m_opstat;
    RxSamplePort<8>     m_opctl;
    std::set<IoDevice*> mIoDevices;

    void _shutdown();
    void _iodev_killall();
    void _iodev_flush();

};


// struct vane::PlatformWindow
// {
//     Platform     *mPlatform;
//     SDL_Window   *mSdlWin;
//     SDL_GLContext mSdlGlCtx;
//     SDL_WindowID  mSdlWinID;

//     // Should be seperated out
//     // --------------------------
//     uint32_t mFBO;
//     uint32_t mVAO;
//     // --------------------------

//     PlatformWindow(Platform*, const char *name, int x, int y, int w, int h);
//     ~PlatformWindow();
//     void update();
//     void updateEvent(SDL_Event&);
// };

#include "platform.inl"
