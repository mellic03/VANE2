#include "vane/service.hpp"

vaneid_t vane::ServiceManager::typeidx_ = 0;


vane::ServiceManager::ServiceManager()
:   mTypeIdxBase(ServiceManager::typeidx_),
    mEnabled(true)
{

}


int vane::ServiceManager::_typeIdxToArrayIdx(vaneid_t typeidx)
{
    size_t idx = typeidx - mTypeIdxBase;

    if (!(idx < mServices.size()))
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

