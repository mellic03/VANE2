#include "gfxapi/gfxapi_gl.hpp"
#include "gfxapi/underlyingtype.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


TextureGl::TextureGl(GfxApiGl &api, int w, int h, const void *data)
:   GfxResourceGl(api)
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


TextureGl::~TextureGl()
{
    gl::DeleteTextures(1, &mId);
}


TextureFormat TextureGl::getTextureFormat() { return mTextureFormat; }
void TextureGl::setTextureFormat(TextureFormat fmt) { mTextureFormat = fmt; }


