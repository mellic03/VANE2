#pragma once

#include "time.hpp"
#include "vane/port.hpp"
#include "vane/type.hpp"
#include "vane/service.hpp"
#include <type_traits>
#include <memory>


namespace vane
{
    class IoDevice;
    class Platform;

    namespace gfxapi
    {
        class GfxApi;
    }

    namespace ioapi
    {
        class IoApi;
    }
}



class vane::Platform: public vane::ServiceManager
{
public:
    ioapi::IoApi   &mIo;
    gfxapi::GfxApi &mGfx;

    Platform(ioapi::IoApi&, gfxapi::GfxApi&);
    bool running();
    void update();
    void shutdown();

private:
    RxSamplePort<OpCtrl>  *mOpAuthRx;
    TxSamplePort<OpState> *mOpStatTx;
    OpCtrl                 mOpAuth;
    OpState                mOpStat;


    void _flushIoDevices();
    void setOpStat(OpState);

};

