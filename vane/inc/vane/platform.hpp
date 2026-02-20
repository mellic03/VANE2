#pragma once

#include "vane/log.hpp"
#include "vane/time.hpp"
#include "vane/type.hpp"
#include "vane/message.hpp"
#include "vane/util/funcptr.hpp"
#include <vector>
#include <set>


namespace vane
{
    class IoDevice;
    class iPlatform;

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



class vane::IoDevice
{
protected:
    vane::iPlatform *mPlatform;
private:
    friend class vane::iPlatform;
    time::PeriodicTimer timer_;
    vaneid_t typeid_;
    bool     kill_;

public:
    IoDevice(iPlatform *p): mPlatform(p), timer_(time::NsTime(0)) {  }
    virtual ~IoDevice() {  }
    virtual void onUpdate() = 0;
    virtual void onEvent(const PlatformEventType&) = 0;
};


class vane::iPlatform
{
protected:
    RxSampleEndpoint<1> mOpAuthRx_;
    TxMsgEndpoint       mOpStatTx_;
    OpState             mOpStat_;
    std::set<IoDevice*> mIoDevices;

    bool _getOpAuth(OpCtrl*);
    void _setOpStat(OpState);

    void _shutdown();
    void _iodev_killall();
    void _iodev_flush();

public:
    iPlatform() {  }
    virtual ~iPlatform() {  }
    virtual void pollevents() = 0;

    void update();
    void shutdown();
    bool active() { return mOpStat_ < OpState::Stopped; }

    template <typename IoDevType, typename... Args>
    IoDevType *iodev_create(Args... args);
    VaneStat   iodev_delete(IoDevice *iodev);

};


#include "platform.inl"











// namespace vane
// {
//     class Platform;

//     enum class OpCtrl: uint8_t
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


// class vane::Platform
// {
// public:
//     struct Impl
//     {
//         OpState (*init)(void);
//         bool (*poll)(Platform&, PlatformEventType*);
//     };

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
//         IoDevice(Platform *p)
//         :   mPlatform(p), timer_(time::NsTime(0)) {  }

//         virtual ~IoDevice() {  }
//         virtual void onUpdate() = 0;
//         virtual void onEvent(const PlatformEventType&) = 0;
//     };


//     Platform(const Platform::Impl&);

//     bool active();
//     void shutdown();
//     void update();

//     template <typename IoDevType, typename... Args>
//     IoDevType *iodev_create(Args... args);
//     VaneStat   iodev_delete(IoDevice *iodev);

// private:
//     Platform::Impl        m_impl;
//     OpState               m_opstat;
//     // RxSamplePortT<OpCtrl> mOpAuthIn;
//     // TxSamplePort<OpState> mOpStatOut;
//     std::set<IoDevice*>   mIoDevices;

//     void _shutdown();
//     void _iodev_killall();
//     void _iodev_flush();

// };


// #include "platform.inl"
