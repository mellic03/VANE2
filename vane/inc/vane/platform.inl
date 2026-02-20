#pragma once

#include "platform.hpp"
#include <filesystem>


// inline vane::iPlatform::iPlatform(const Platform::Impl &impl)
// :   m_impl(impl),
//     m_opstat(OpState::Starting)
// {
//     // if (!opAuthTx.rxopen(&mOpAuthIn))
//     // {
//     //     VLOG_ERROR("Failed to connect mOpAuthIn");
//     // }

//     // if (!mOpStatOut.rxopen(&opStateRx))
//     // {
//     //     VLOG_ERROR("Failed to connect mOpStatOut");
//     // }

//     m_opstat = m_impl.init();

//     VLOG_INFO("Platform initialized");
// }

inline bool vane::iPlatform::_getOpAuth(OpCtrl *ctrl)
{
    // mOpAuthRx_.
    return false;
}

inline void vane::iPlatform::_setOpStat(OpState stat)
{
    // static OpState
    std::memcpy(&mOpStat_, &stat, sizeof(OpState));
    static uint64_t buf[4];
    memcpy(buf, static_cast<void*>(&stat), sizeof(OpState));
    mOpStatTx_.sendmsg_bcast(buf, sizeof(OpState));
}


inline void vane::iPlatform::shutdown()
{
    VLOG_INFO("Shutdown initiated");

    _setOpStat(OpState::Stopping);

    _iodev_killall();
    _iodev_flush();

    _setOpStat(OpState::Stopped);

    VLOG_INFO("Shutdown complete");
}


inline void vane::iPlatform::update()
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

    this->pollevents();

    _iodev_flush();
}



template <typename T, typename... Args>
inline T *vane::iPlatform::iodev_create(Args... args)
{
    static_assert( std::is_base_of_v<IoDevice, T>,
                    "T must be derivative of vane::iPlatform::IoDevice" );

    auto *obj = new T(this, args...);
    auto *iodev = static_cast<IoDevice*>(obj);
          iodev->typeid_ = vane_typeid<T>();
          iodev->kill_   = false;
    mIoDevices.insert(iodev);

    return obj;
}


inline vane::VaneStat vane::iPlatform::iodev_delete(IoDevice *iodev)
{
    iodev->kill_ = true;
    return VaneStat::OK;
}


inline void vane::iPlatform::_iodev_killall()
{
    for (IoDevice *iodev: mIoDevices)
    {
        iodev->kill_ = true;
    }
}

inline void vane::iPlatform::_iodev_flush()
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


