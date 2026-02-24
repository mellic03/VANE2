#pragma once

#include "vane/gfxapi/fwd.hpp"


class vane::gfxapi::Texture: public GfxResource
{
public:
    TextureFormat mTextureFormat;

    Texture(int w, int h, const void *data);
    Texture(Texture&&);
    Texture &operator=(Texture&&);
    ~Texture();

    TextureFormat getTextureFormat();
    void setTextureFormat(TextureFormat);

};

