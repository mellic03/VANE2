#pragma once

#include "time.hpp"
#include "vane/port.hpp"
#include "vane/type.hpp"
#include <type_traits>
#include <memory>


namespace vane
{
    class IoDevice;
    class Window;
    class Platform;
}



class vane::Platform
{
private:
    void _addIoDevice(IoDevice*);

public:
    Platform();

    bool running();
    void update();
    void shutdown();

    template <typename T, typename... Args>
    T   *makeIoDevice(Args... args);
    bool freeIoDevice(IoDevice *iodev);


private:
    std::vector<std::unique_ptr<IoDevice>> mIoDevices;

    RxSamplePort<OpCtrl>  *mOpAuthRx;
    TxSamplePort<OpState> *mOpStatTx;
    OpCtrl                 mOpAuth;
    OpState                mOpStat;

    void _flushIoDevices();
    void setOpStat(OpState);

};


template <typename T, typename... Args>
inline T *vane::Platform::makeIoDevice(Args... args)
{
    static_assert(std::is_base_of_v<IoDevice, T>, "T must be derivative of vane::IoDevice" );

    T *iodev = new T(this, args...);
       iodev->typeid_ = vane_typeid<T>();
       iodev->kill_   = false;

    mIoDevices.push_back(std::unique_ptr<IoDevice>(iodev));

    return iodev;
}


inline bool vane::Platform::freeIoDevice(IoDevice *iodev)
{
    iodev->kill_ = true;
    // if (mIoDevices.)
    return true;
}
