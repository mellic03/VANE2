#pragma once

#include "vane/log.hpp"
#include "vane/time.hpp"
#include "vane/type.hpp"
#include "vane/util/funcptr.hpp"
#include <vector>
#include <set>


// namespace vane
// {
//     enum class OpCtl: uint8_t
//     {
//         None       = 0,
//         Initialize = 1,
//         Terminate  = 2
//     };

//     enum class OpState: uint8_t
//     {
//         Invalid  = 0,
//         Starting,
//         Running,
//         Stopping,
//         Stopped
//     };
// }

// namespace vane
// {
//     class Platform;

//     class IoDevice
//     {
//     protected:
//         vane::Platform *mPlatform;
//     private:
//         friend class vane::Platform;
//         time::PeriodicTimer timer_;
//         vaneid_t typeid_;
//         bool     kill_;

//     public:
//         IoDevice(Platform *p): mPlatform(p), timer_(time::NsTime(0)) {  }
//         virtual ~IoDevice() {  }
//         virtual void onUpdate() = 0;
//         virtual void onEvent(const PlatformEventType&) = 0;
//     };

// }


// class vane::Platform
// {
// public:
//     bool active();
//     void shutdown();
//     void update();

//     template <typename IoDevType, typename... Args>
//     IoDevType *iodev_create(Args... args);
//     VaneStat   iodev_delete(IoDevice *iodev);

// private:
//     struct ThisState {
//         static constexpr int ALIVE = 2;
//         static constexpr int DYING = 1;
//         static constexpr int DEAD  = 0;
//     };

//     RxSamplePortT<OpCtl>  mOpAuthIn;
//     TxSamplePort<OpState> mOpStatOut;
//     OpState               m_opstate;
//     std::set<IoDevice*>   mIoDevices;

//     void _shutdown();
//     void _iodev_killall();
//     void _iodev_flush();

// };


// #include "platform.inl"











namespace vane
{
    class Platform;

    enum class OpCtrl: uint8_t
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


    Platform(const Platform::Impl&);

    bool active();
    void shutdown();
    void update();

    template <typename IoDevType, typename... Args>
    IoDevType *iodev_create(Args... args);
    VaneStat   iodev_delete(IoDevice *iodev);

private:
    Platform::Impl        m_impl;
    OpState               m_opstat;
    // RxSamplePortT<OpCtrl> mOpAuthIn;
    // TxSamplePort<OpState> mOpStatOut;
    std::set<IoDevice*>   mIoDevices;

    void _shutdown();
    void _iodev_killall();
    void _iodev_flush();

};


#include "platform.inl"
