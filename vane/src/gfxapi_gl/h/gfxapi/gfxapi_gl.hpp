// #pragma once

// #include "vane/gfxapi.hpp"

// namespace vane::gfxapi
// {
//     class GfxApiGl;
// }


// #define FramebufferType vane::gfxapi::Framebuffer<vane::gfxapi::GfxApiGl>
// #define TextureType vane::gfxapi::Texture<vane::gfxapi::GfxApiGl>


// template<>
// class FramebufferType
// {
// public:
//     Framebuffer(GfxApiGl &api);
// };

// template<>
// class TextureType
// {
// public:
//     Texture(GfxApiGl &api);
// };


// class vane::gfxapi::GfxApiGl: public vane::gfxapi::GfxApi<GfxApiGl>
// {
// public:
//     FramebufferType createFramebuffer();
//     TextureType createTexture();
// };

