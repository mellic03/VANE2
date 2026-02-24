#pragma once

#include "vane/ioapi.hpp"
#include "vane/gfxapi.hpp"
#include "vane/port.hpp"
#include "time.hpp"

#include <type_traits>
#include <memory>


namespace vane
{
    class IoDevice;
    class Platform;
}



class vane::Platform: public vane::ServiceManager
{
public:
    // Platform(IoApi&, GfxApi&);
    Platform();
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

