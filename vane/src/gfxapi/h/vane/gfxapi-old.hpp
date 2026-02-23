// #pragma once

// #include <memory>


// namespace vane::gfxapi
// {
//     class GfxApi;
//     class Window;
//     class Framebuffer;
//     class Texture;
//     class ShaderProgram;
//     class ComputeProgram;

//     using WindowPtr         = std::shared_ptr<Window>;
//     using FramebufferPtr    = std::shared_ptr<Framebuffer>;
//     using TexturePtr        = std::shared_ptr<Texture>;
//     using ShaderProgramPtr  = std::shared_ptr<ShaderProgram>;
//     using ComputeProgramPtr = std::shared_ptr<ComputeProgram>;


//     extern GfxApi *getGfxApi();

//     enum class TextureFormat
//     {
//         RED_U8,
//         RGB_U8,
//         RGBA_U8,
//         RGBA_U32,
//         RGBA_F16,
//         RGBA_F32
//     };

// }



// class vane::gfxapi::GfxApi
// {
// public:
//     virtual ~GfxApi() {  }

//     virtual WindowPtr getMainWindow() = 0;

//     virtual WindowPtr         createWindow(const char *name, int w, int h) = 0;
//     virtual FramebufferPtr    createFramebuffer() = 0;
//     virtual TexturePtr        createTexture(int w, int h, const void *data) = 0;
//     virtual ShaderProgramPtr  createShaderProgram(const char *v, const char *f) = 0;
//     virtual ComputeProgramPtr createComputeProgram(const char *c) = 0;

// };


// #include <vane/objmanager.hpp>

// class vane::gfxapi::Window
// {
// public:
//     virtual ~Window() {  }
//     virtual void onUpdate() = 0;
//     virtual void onEvent(void*) = 0;
//     virtual void setFramebufferSrc(const std::shared_ptr<Framebuffer>&) = 0;

// };


// class vane::gfxapi::Framebuffer
// {
// private:
//     struct Impl;
//     Impl *m_impl;

// public:
//     virtual ~Framebuffer() {  }
//     virtual void setTextureDst(const std::shared_ptr<Texture>&) = 0;

// };


// class vane::gfxapi::Texture
// {
// private:
//     struct Impl;
//     Impl *m_impl;

// public:
//     virtual ~Texture() {  }
//     virtual TextureFormat getTextureFormat() = 0;
//     virtual void setTextureFormat(TextureFormat) = 0;

// };



// class vane::gfxapi::ShaderProgram
// {
// private:
//     struct Impl;
//     Impl *m_impl;

// public:
//     virtual ~ShaderProgram() {  }
// };


// class vane::gfxapi::ComputeProgram
// {
// private:
//     struct Impl;
//     Impl *m_impl;

// public:
//     virtual ~ComputeProgram() {  }
// };



