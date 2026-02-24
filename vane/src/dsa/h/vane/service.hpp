#pragma once

#include "vane/inplace_queue.hpp"
#include <memory>
#include <vector>


namespace vane
{
    using srvmsg_t = int32_t;

    struct SrvMsg {
        static constexpr srvmsg_t INVALID  = 0;
        static constexpr srvmsg_t PAUSE    = 1;
        static constexpr srvmsg_t RESUME   = 2;
        static constexpr srvmsg_t SHUTDOWN = 3;
    };


    class Service;
    class ServiceManager;


    class ServiceManager: public vane::NonCopyable
    {
    private:
        static int typeidx_;
        const  int mTypeIdxBase;
        int _typeIdxToArrayIdx(int typeidx);

    protected:
        std::vector<vane::Service*> mServices;

    public:
        ServiceManager();
        void update();

        template <typename T, typename... Args>
        T *registerService(Args...);

        template <typename T>
        T *getService();

        // void deleteService(vane::Service*);

        template <typename T>
        int srvMsgToSrv(srvmsg_t msg);

        template <typename T>
        int srvRunCmd(int cmd, void *arg);

        int srvMsgToAll(srvmsg_t msg);
    };


    class Service: public vane::NonCopyable
    {
    private:
        friend class ServiceManager;
        bool   mBrandOfSacrifice;
        size_t mVaneTypeId;
        int    mTypeIdx;
        ServiceManager *mSrvManager;
        inplace_queue<srvmsg_t, 64> mMessageQueue;

    protected:
        /**
         * @return Number of services messaged
         */
        template <typename T>
        int srvMsgToSrv(srvmsg_t msg) { return mSrvManager->srvMsgToSrv<T>(msg); }
        int srvMsgToAll(srvmsg_t msg) { return mSrvManager->srvMsgToAll(msg); }

        template <typename T>
        int srvRunCmd(int cmd, void *arg) { return mSrvManager->srvRunCmd<T>(cmd, arg); }

        template <typename T>
        T *getService() { return mSrvManager->getService<T>(); }

    public:
        Service(): mBrandOfSacrifice(false), mVaneTypeId(0) {  };
        ~Service() {  };

        virtual void onUpdate() = 0;
        virtual void onEnable()   {  };
        virtual void onDisable()  {  };
        virtual void onShutdown() {  };
        virtual void onMsgRecv(srvmsg_t) = 0;
        virtual int  onCmdRecv(int, void*) { return -1; };

    };

}



template <typename T, typename... Args>
inline T *vane::ServiceManager::registerService(Args... args)
{
    static_assert(
        std::is_base_of_v<Service, T>,
        "T must be derivative of vane::Service"
    );

    if (getService<T>())
    {
        VLOG_ERROR("Attempted to register VaneTypeId=={} more than once\n", vane_typeid<T>());
        return nullptr;
    }

    T *srv = new T(args...);
       srv->mBrandOfSacrifice = false;
       srv->mVaneTypeId = vane_typeid<T>();
       srv->mTypeIdx    = srv_typeid<T>();
       srv->mSrvManager = this;
    mServices.push_back(srv);

    int idx_maybe = _typeIdxToArrayIdx(srv_typeid<T>()); 

    VLOG_INFO(
        "Registered service (VaneTypeId, TypeIdx, Idx, idx_maybe) == ({}, {}, {}, {})",
        srv->mVaneTypeId, srv->mTypeIdx, mServices.size() - 1, idx_maybe
    );

    return srv;
}


template <typename T>
inline T *vane::ServiceManager::getService()
{
    static_assert(
        std::is_base_of_v<Service, T>,
        "T must be derivative of vane::Service"
    );

    const size_t desired_id = srv_typeid<T>();
    for (auto *srv: mServices)
        if (srv->mTypeIdx == desired_id)
            return static_cast<T*>(srv);
    return nullptr;
}


// inline void vane::ServiceManager::deleteService(Service *srv)
// {
//     srv->mBrandOfSacrifice = true;
// }


template <typename T>
inline int vane::ServiceManager::srvMsgToSrv(srvmsg_t msg)
{
    // static_assert(
    //     std::is_base_of_v<Service, T>,
    //     "T must be derivative of vane::Service"
    // );

    const size_t desired_id = srv_typeid<T>();
    for (auto *srv: mServices)
    {
        if (srv->mTypeIdx == desired_id)
        {
            srv->mMessageQueue.push(msg);
            return 1;
        }
    }

    return -1;
}


inline int vane::ServiceManager::srvMsgToAll(srvmsg_t msg)
{
    int count = 0;

    for (auto *srv: mServices)
    {
        srv->mMessageQueue.push(msg);
        count += 1;
    }

    return count;
}



template <typename T>
inline int vane::ServiceManager::srvRunCmd(int cmd, void *arg)
{
    auto *srv = static_cast<Service*>(getService<T>());
    if (srv == nullptr)
        return -1;
    return srv->onCmdRecv(cmd, arg);
}
