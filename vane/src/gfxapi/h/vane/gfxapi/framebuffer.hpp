#pragma once

#include "vane/gfxapi/fwd.hpp"


class vane::gfxapi::Framebuffer: public GfxResource
{
public:
    TexturePtr mTexture;
    void _check_status();

    Framebuffer();
    Framebuffer(Texture&&);
    ~Framebuffer();
    void setTextureDst(const TexturePtr&);
};
