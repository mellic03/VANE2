#pragma once

#include <memory>


namespace vane::gfxapi
{
    class GfxApi;
    class Window;
    class Framebuffer;
    class Texture;
    class ShaderProgram;
    class ComputeProgram;

    extern GfxApi *getGfxApi();

    enum class TextureFormat
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
    virtual ~GfxApi() {  }

    virtual std::unique_ptr<Window> createWindow(const char *name, int w, int h) = 0;
    virtual std::unique_ptr<Framebuffer> createFramebuffer() = 0;
    virtual std::unique_ptr<Texture> createTexture(int w, int h, const void *data) = 0;
    virtual std::unique_ptr<ShaderProgram> createShaderProgram(const char *v, const char *f) = 0;
    virtual std::unique_ptr<ComputeProgram> createComputeProgram(const char *c) = 0;

};



class vane::gfxapi::Window
{
public:
    virtual ~Window() {  }
    virtual void setFramebufferSrc(const std::shared_ptr<Framebuffer>&) = 0;

};


class vane::gfxapi::Framebuffer
{
public:
    virtual ~Framebuffer() {  }
    virtual void setTextureDst(const std::shared_ptr<Texture>&) = 0;

};


class vane::gfxapi::Texture
{
public:
    virtual ~Texture() {  }
    virtual TextureFormat getTextureFormat() = 0;
    virtual void setTextureFormat(TextureFormat) = 0;

};



class vane::gfxapi::ShaderProgram
{
public:
    virtual ~ShaderProgram() {  }
};


class vane::gfxapi::ComputeProgram
{
public:
    virtual ~ComputeProgram() {  }
};



