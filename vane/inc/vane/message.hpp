#pragma once

#include <cstddef>
#include <cstdint>

namespace vane
{
    class RxMsgEndpoint;
    class TxMsgEndpoint;
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
};

