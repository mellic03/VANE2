#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include "vane/log.hpp"

namespace vane
{
    class RxMsgEndpoint;
    class TxMsgEndpoint;

    template <size_t N>
    class RxSampleEndpoint;
}


class vane::RxMsgEndpoint
{
private:
    friend class vane::TxMsgEndpoint;
    uint32_t addr;

public:
    virtual void recvmsg(const void*, size_t) = 0;

};


class vane::TxMsgEndpoint
{
private:
    static constexpr uint32_t MAX_RXERS = 32;
    RxMsgEndpoint *m_rxers[MAX_RXERS];
    uint32_t       m_rxidx = 0;

public:
    RxMsgEndpoint *rxopen(RxMsgEndpoint *rxer);

    void sendmsg_bcast(const void *msg, size_t msgsz);
    void sendmsg_mcast(uint32_t mask, const void *msg, size_t msgsz);
    void sendmsg_ucast(uint32_t dest, const void *msg, size_t msgsz);

    template <typename T>
    void sendmsg_bcast(const T &p) { sendmsg_bcast(&p, sizeof(T)); }

};




template <size_t N>
class vane::RxSampleEndpoint: public vane::RxMsgEndpoint
{
private:
alignas(max_align_t)
    uint8_t data_[N];
    size_t  size_;
    bool    ready_;

public:
    RxSampleEndpoint(): size_(0), ready_(false) {  };

    virtual void recvmsg(const void *msg, size_t msgsz) final
    {
        if (msgsz > N)
        {
            VLOG_ERROR("RxSamplePort msgsz > N");
            return;
        }
        std::memcpy(data_, msg, msgsz);
        size_  = msgsz;
        ready_ = true;
    }

    // size_t read(void *buf, size_t bufsz)
    // {
    //     size_t sz = vane_min(size_, bufsz);

    //     if (sz > 0)
    //     {
    //         memcpy(buf, data_, sz);
    //         size_ = 0;
    //     }

    //     return sz;
    // }

    void *get()
    {
        if (!ready_)
            return nullptr;
        ready_ = false;
        return static_cast<void*>(data_);
    }

};