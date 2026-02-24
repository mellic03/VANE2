#pragma once

#include "vane/type.hpp"
#include "vane/log.hpp"
#include <string>

namespace vane::file
{
    std::string loadRaw(const std::string &path);
    size_t load_raw(const char *filepath, void *buf, size_t bufsz);
}


namespace vane
{
    template <size_t N>
    class FileReader: public vane::NonCopyable
    {
    private:
        alignas (std::max_align_t)
        uint8_t m_data[N];
        size_t  m_size;

    public:
        const char *mData;
        size_t mSize;

        FileReader(): mSize(0) {  };

        bool loadFile(const char *filepath);
        // const char*  data() const { return (const char*)mData }
        // const size_t size() const { return mSize; }

    };
}


template <size_t N>
bool vane::FileReader<N>::loadFile(const char *filepath)
{
    m_size = vane::file::load_raw(filepath, m_data, N);
    mData = (const char*)m_data;
    mSize = m_size;

    VLOG_INFO("FileReader<{}> loaded {} bytes", N, mSize);

    return 0<=mSize && mSize<N;
}

