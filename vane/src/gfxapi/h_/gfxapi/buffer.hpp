
#pragma once

#include "vane/gfxapi.hpp"


namespace vane::gfxapi
{
    class UboWrapper: public GfxResource
    {
    protected:
        const char *mName;
        const size_t mSize;
        void  *mData;

    public:
        UboWrapper(const char *name);
        UboWrapper(const char *name, size_t size);
        ~UboWrapper();
        void bindToProgram(ShaderProgram*);
        void sendToGpu();

    };


    template <typename T>
    class UboWrapperT: public UboWrapper
    {
    private:
        T &mObject;

    public:
        UboWrapperT(const char *name)
        :   UboWrapper(name, sizeof(T)),
            mObject(*(new (mData) T()))
        {
            
        }

        T &get() { return mObject; }
    };
}
