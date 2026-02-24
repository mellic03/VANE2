#include "vane/service.hpp"


int vane::ServiceManager::typeidx_ = 0;


vane::ServiceManager::ServiceManager()
:   mTypeIdxBase(ServiceManager::typeidx_)
{

}


int vane::ServiceManager::_typeIdxToArrayIdx(int typeidx)
{
    int idx = typeidx - mTypeIdxBase;

    if (!(0<=idx && idx<mServices.size()))
    {
        return -1;
    }

    return idx;
}



void vane::ServiceManager::update()
{
    for (auto *srv: mServices)
    {
        srv->onUpdate();
    }

    for (auto *srv: mServices)
    {
        while (false == srv->mMessageQueue.empty())
        {
            uint32_t msg = srv->mMessageQueue.front();
                           srv->mMessageQueue.pop();
            if (msg == SrvMsg::SHUTDOWN)
                srv->mBrandOfSacrifice = true;
            else
                srv->onMsgRecv(msg);
        }
    }

    for (int i=mServices.size()-1; i>=0; i--)
    {
        if (mServices[i]->mBrandOfSacrifice)
        {
            std::swap(mServices[i], mServices.back());
            delete mServices.back();
            mServices.pop_back();
        }
    }
}

