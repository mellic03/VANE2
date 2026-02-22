#pragma once

#include "vane/gfxapi.hpp"


namespace vane::gfxapi
{
    using IdType = GLuint;

    class GfxApi;

    class GfxResource;
    class Framebuffer;
    class Texture;

    enum class TextureFormat: int8_t
    {
        RED_U8,
        RGB_U8,
        RGBA_U8,
        RGBA_U32,
        RGBA_F16,
        RGBA_F32
    };
}



class vane::gfxapi::GfxApi
{
public:
    Framebuffer &createFramebuffer();
    Texture &createTexture(int w, int h);

};


class vane::gfxapi::GfxResource
{
protected:
    friend class GfxApi;
    GfxApi &mApi;
    IdType mId;
    GfxResource(GfxApi&);

public:
    IdType getId();

};


class vane::gfxapi::Framebuffer: public GfxResource
{
private:
    Framebuffer(GfxApi&);

public:
    void setTarget(const Texture&);

};


class vane::gfxapi::Texture: public GfxResource
{
private:
    TextureFormat mTextureFormat;
    Texture(GfxApi&, int w, int h, const void *data);

public:
    const TextureFormat &getTextureFormat() const;
    void setTextureFormat(const TextureFormat&);

};



