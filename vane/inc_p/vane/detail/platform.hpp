#pragma once

#include "vane/log.hpp"
#include "vane/time.hpp"
#include "vane/type.hpp"
#include <vector>
#include <memory>


namespace vane
{
    class IoDevice;
    class Window;
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


class vane::IoDevice
{
protected:
    vane::Platform *mPlatform;
private:
    friend class vane::Platform;
    time::PeriodicTimer timer_;
    vaneid_t typeid_;
    bool     kill_;

public:
    IoDevice(Platform *p): mPlatform(p), timer_(time::NsTime(0)) {  }
    virtual ~IoDevice() {  }
    virtual void onUpdate() = 0;
    virtual void onEvent(void*) = 0;
};



// class vane::Window: public vane::IoDevice
// {
// protected:
//     struct Impl;
//     std::unique_ptr<Impl> m_impl;

// public:
//     Window(Platform*, const char *name, int w, int h);
//     virtual ~Window() final;
//     virtual void onUpdate() final;
//     virtual void onEvent(void*) final;

// };




class vane::Platform
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;

    void _addIoDevice(IoDevice*);

public:
    Platform();

    void update();
    bool active();
    void shutdown();

    template <typename T, typename... Args>
    inline T *iodev_create(Args... args)
    {
        static_assert(std::is_base_of_v<IoDevice, T>, "T must be derivative of vane::IoDevice" );

        T *iodev = new T(this, args...);
           iodev->typeid_ = vane_typeid<T>();
           iodev->kill_   = false;
    
        _addIoDevice(iodev);

        return iodev;
    }

    inline vane::VaneStat iodev_delete(IoDevice *iodev)
    {
        iodev->kill_ = true;
        return VaneStat::OK;
    }

};

