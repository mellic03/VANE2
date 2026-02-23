#pragma once

#include "time.hpp"
#include "vane/port.hpp"
#include "vane/type.hpp"
#include "vane/objmanager.hpp"
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
}



class vane::Platform: public vane::ObjectManager
{
public:
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

