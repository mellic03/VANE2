#include "gfxapi/gfxapi_gl.hpp"

using namespace vane::gfxapi;


Texture::Texture(int w, int h, const void *data)
:   GfxResource(0)
{
    mTextureFormat = TextureFormat::RGB_U8;
    auto internalformat = toUnderlyingType(mTextureFormat);

    gl::CreateTextures(GL_TEXTURE_2D, 1, &mId);
    gl::TextureParameteri(mId, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(mId, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(mId, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::TextureParameteri(mId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    gl::TextureStorage2D(mId, 1, GL_RGBA8, w, h);
    gl::TextureSubImage2D(mId, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // gl::TextureStorage2D(mId, 1, GL_DEPTH_COMPONENT24, w, h);
    // gl::TextureSubImage2D(mId, 0, 0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, data);

}


Texture::Texture(Texture &&tex)
:   GfxResource(tex.mId), mTextureFormat(tex.mTextureFormat)
{

}


Texture &Texture::operator=(Texture &&tex)
{
    mId = tex.mId;
    mTextureFormat = tex.mTextureFormat;
    return *this;
}


Texture::~Texture()
{
    gl::DeleteTextures(1, &mId);
}


TextureFormat Texture::getTextureFormat() { return mTextureFormat; }
void Texture::setTextureFormat(TextureFormat fmt) { mTextureFormat = fmt; }


