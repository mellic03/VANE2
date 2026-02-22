#include "gfxapi/underlyingtype.hpp"
#include "gfxapi/gl.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


template<>
struct as_underlying<TextureFormat> { using type = GLenum; };



template <>
GLenum vane::gfxapi::toUnderlyingType(const TextureFormat &from)
{
    switch (from)
    {
        case TextureFormat::RED_U8:   return GL_RED;
        case TextureFormat::RGB_U8:   return GL_RGB8;
        case TextureFormat::RGBA_U8:  return GL_RGBA8;
        case TextureFormat::RGBA_U32: return GL_RGBA32UI;
        case TextureFormat::RGBA_F16: return GL_RGBA16F;
        case TextureFormat::RGBA_F32: return GL_RGBA32F;
        default:
            VLOG_ERROR("toUnderlyingType<GLenum, gfxapi::TextureFormat> unknown conversion");
            break;
    }
}


template <>
TextureFormat vane::gfxapi::fromUnderlyingType<TextureFormat>(const GLenum &from)
{
    switch (from)
    {
        case GL_RED:      return TextureFormat::RED_U8;
        case GL_RGB8:     return TextureFormat::RGB_U8;
        case GL_RGBA8:    return TextureFormat::RGBA_U8;
        case GL_RGBA32UI: return TextureFormat::RGBA_U32;
        case GL_RGBA16F:  return TextureFormat::RGBA_F16;
        case GL_RGBA32F:  return TextureFormat::RGBA_F32;
        default:
            VLOG_ERROR("toUnderlyingType<GLenum, gfxapi::TextureFormat> unknown conversion");
            break;
    }
}




