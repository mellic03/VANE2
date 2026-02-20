#pragma once

#include "message.hpp"
#include "util/align.hpp"
#include "log.hpp"

#include <cstring>

template <typename T> T vane_min(T a, T b) { return (a < b) ? a : b; }
template <typename T> T vane_max(T a, T b) { return (a > b) ? a : b; }


template <size_t N>
class RxSamplePort: public vane::RxMsgEndpoint
{
private:
    size_t size_;
    alignas(max_align_t) uint8_t data_[N];

public:
    RxSamplePort(): size_(0) {  };

    virtual void recvmsg(const void *msg, size_t msgsz) final
    {
        if (msgsz < N)
        {
            size_ = msgsz;
            std::memcpy(data_, msg, size_);
        }
        else
        {
            VLOG_ERROR("RxSamplePort msgsz != sizeof(T)");
        }
    }

    size_t read(void *buf, size_t bufsz)
    {
        size_t sz = vane_min(size_, bufsz);

        if (sz > 0)
        {
            memcpy(buf, data_, sz);
            size_ = 0;
        }

        return sz;
    }
};


template <typename T>
class RxSamplePortT: public vane::RxMsgEndpoint
{
private:
    bool ready_;
    T data_[1];

public:
    RxSamplePortT(): ready_(false) {  };

    virtual void recvmsg(const void *msg, size_t msgsz) final
    {
        if (msgsz != sizeof(T))
        {
            VLOG_ERROR("RxSamplePortT msgsz != sizeof(T)");
            return;
        }

        std::memcpy(data_, msg, sizeof(T));
        ready_ = true;
    }

    bool read(T *data)
    {
        if (!ready_)
            return false;

        ready_ = false;
        memcpy(data, data_, sizeof(T));
        return true;
    }
};




template <typename T>
class TxSamplePort: public vane::TxMsgEndpoint
{
public:
    void write(const T &data)
    {
        sendmsg_bcast<T>(data);
    }
};

