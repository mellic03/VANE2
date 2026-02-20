#pragma once

#include "platform.hpp"
#include <filesystem>


inline vane::Platform::Platform(const Platform::Impl &impl)
:   m_impl(impl),
    m_opstat(OpState::Starting)
{
    // if (!opAuthTx.rxopen(&mOpAuthIn))
    // {
    //     VLOG_ERROR("Failed to connect mOpAuthIn");
    // }

    // if (!mOpStatOut.rxopen(&opStateRx))
    // {
    //     VLOG_ERROR("Failed to connect mOpStatOut");
    // }

    m_opstat = m_impl.init();

    VLOG_INFO("Platform initialized");
}


inline bool vane::Platform::active()
{
    return (m_opstat < OpState::Stopped);
}


inline void vane::Platform::shutdown()
{
    VLOG_INFO("Shutdown initiated");

    m_opstat = OpState::Stopping;

    _iodev_killall();
    _iodev_flush();

    m_opstat = OpState::Stopped;

    VLOG_INFO("Shutdown complete");
}


inline void vane::Platform::update()
{
    // OpCtrl opAuthIn;
    // if (mOpAuthIn.read(&opAuthIn))
    // {
    //     printf("opAuthIn: 0x%x\n", opAuthIn);
    // }

    if (mIoDevices.empty())
    {
        this->shutdown();
        return;
    }

    for (auto *iodev: mIoDevices)
    {
        iodev->onUpdate();
    }

    PlatformEventType e;

    while (m_impl.poll(*this, &e))
    {
        for (auto *iodev: mIoDevices)
        {
            iodev->onEvent(e);
        }

        _iodev_flush();
    }

    _iodev_flush();
}



template <typename T, typename... Args>
inline T *vane::Platform::iodev_create(Args... args)
{
    static_assert( std::is_base_of_v<IoDevice, T>,
                    "T must be derivative of vane::Platform::IoDevice" );

    auto *obj = new T(this, args...);
    auto *iodev = static_cast<IoDevice*>(obj);
          iodev->typeid_ = vane_typeid<T>();
          iodev->kill_   = false;
    mIoDevices.insert(iodev);

    return obj;
}


inline vane::VaneStat vane::Platform::iodev_delete(IoDevice *iodev)
{
    iodev->kill_ = true;
    return VaneStat::OK;
}


inline void vane::Platform::_iodev_killall()
{
    for (IoDevice *iodev: mIoDevices)
    {
        iodev->kill_ = true;
    }
}

inline void vane::Platform::_iodev_flush()
{
    for (auto it=mIoDevices.begin(); it!=mIoDevices.end();)
    {
        IoDevice *iodev = *it;

        if (iodev->kill_)
        {
            it = mIoDevices.erase(it);
            delete iodev;
        }

        else
        {
            ++it;
        }
    }
}


