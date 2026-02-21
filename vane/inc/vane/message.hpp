#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include "vane/log.hpp"

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
protected:
    uint32_t m_rxaddr;
    std::vector<std::unique_ptr<RxMsgEndpoint>> m_rxers;

public:
    TxMsgEndpoint(): m_rxaddr(0) {  }
    // RxMsgEndpoint *bind(RxMsgEndpoint *rxer);

    template <typename RxType>
    inline RxType *makeRxEndpoint()
    {
        static_assert(
            std::is_base_of_v<RxMsgEndpoint, RxType>,
            "RxType must be derivative of vane::RxMsgEndpoint"
        );

        auto *rxer = static_cast<RxMsgEndpoint*>(new RxType());
              rxer->addr = m_rxaddr++;
        m_rxers.push_back(std::unique_ptr<RxMsgEndpoint>(rxer));

        return rxer;
    }

    // void broadcast(const void *msg, size_t msgsz);
    // void multicast(uint32_t mask, const void *msg, size_t msgsz);
    // void unicast(uint32_t dest, const void *msg, size_t msgsz);

    // template <typename T>
    // void sendmsg_bcast(const T &p) { sendmsg_bcast(&p, sizeof(T)); }

};

