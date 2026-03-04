
#pragma once

#include "vane/gfxapi.hpp"


namespace vane::gfxapi
{
    class UboGpuOnly: public GfxResource
    {
    protected:
        const char *mName;
        const size_t mSize;

    public:
        UboGpuOnly(const char *name, size_t size);
        ~UboGpuOnly();
        void bindToProgram(ShaderProgram*);
        void write(size_t offset, size_t nbytes, const void *src);
    };


    class UboGpuCpu: public UboGpuOnly
    {
    protected:
        void *mData;

    public:
        UboGpuCpu(const char *name, size_t size);
        ~UboGpuCpu();
        void write(size_t offset, size_t nbytes, const void *src);
        void sendToGpu();
    };


    template <typename T>
    class UboWrapperT: public UboGpuCpu
    {
    private:
        T &mObject;

    public:
        UboWrapperT(const char *name)
        :   UboGpuCpu(name, sizeof(T)),
            mObject(*static_cast<T*>(mData))
        {
            static_assert(std::is_standard_layout_v<T>, "T must be standard layout");
        }

        T &get()
        {
            return mObject;
        }
    };
}



namespace vane::gfxapi
{
    class SsboGpuOnly: public GfxResource
    {
    protected:
        const char *mName;
        const size_t mSize;

    public:
        SsboGpuOnly(const char *name, size_t size);
        ~SsboGpuOnly();
        void bindToProgram(ShaderProgram*);
        void bindToProgramIndex(uint32_t idx);
        void write(size_t offset, size_t nbytes, const void *src);
    };
}

