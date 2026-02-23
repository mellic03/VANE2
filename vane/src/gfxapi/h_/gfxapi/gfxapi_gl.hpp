#pragma once

#include <SDL3/SDL.h>
#include "vane/gfxapi.hpp"
#include "gfxapi/gl.hpp"
#include "gfxapi/underlyingtype.hpp"
// #include <memory>
// #include <vector>


// namespace vane::gfxapi
// {
//     class GfxApi;
//     class GfxResource;
//     class WindowRaii;
//     class Window;
//     class Framebuffer;
//     class Texture;
//     class GpuProgram;
//     class ShaderProgram;
//     class ComputeProgram;

//     using WindowPtr         = std::shared_ptr<Window>;
//     using FramebufferPtr    = std::shared_ptr<Framebuffer>;
//     using TexturePtr        = std::shared_ptr<Texture>;
//     using ShaderProgramPtr  = std::shared_ptr<ShaderProgram>;
//     using ComputeProgramPtr = std::shared_ptr<ComputeProgram>;
// }




// class vane::gfxapi::GfxApi: public gfxapi::GfxApi
// {
// private:

//     GfxApi &mBaseApi;
//     WindowPtr mMainWindow;

//     std::vector<WindowPtr>         mWindows;
//     std::vector<FramebufferPtr>    mFramebuffers;
//     std::vector<TexturePtr>        mTextures;
//     std::vector<ShaderProgramPtr>  mShaderPrograms;
//     std::vector<ComputeProgramPtr> mComputePrograms;


// public:
//     GfxApi();

//     virtual WindowPtr getMainWindow() final;

//     WindowPtr         createWindow(const char *name, int w, int h);
//     FramebufferPtr    createFramebuffer();
//     TexturePtr        createTexture(int w, int h, const void *data);
//     ShaderProgramPtr  createShaderProgram(const char *v, const char *f);
//     ComputeProgramPtr createComputeProgram(const char *c);

//     virtual WindowPtr         createWindow(const char *name, int w, int h) final;
//     virtual FramebufferPtr    createFramebuffer() final;
//     virtual TexturePtr        createTexture(int w, int h, const void *data) final;
//     virtual ShaderProgramPtr  createShaderProgram(const char *vpath, const char *fpath) final;
//     virtual ComputeProgramPtr createComputeProgram(const char *cpath) final;

//     template <typename T, typename... Args>
//     std::unique_ptr<T> create(Args... args)
//     {
//         return std::unique_ptr<T>(new T(*this, args...));
//     }

//     // template <typename T, typename... Args>
//     // std::shared_ptr<T> create_shared(Args... args)
//     // { return std::create<T>(args...); }

// };


// class vane::gfxapi::GfxResource
// {
// public:
//     GfxApi &mApi;
//     GLuint    mId;

//     GfxResource(GfxApi &api, GLuint id=0)
//     :   mApi(api), mId(id) {  };

// };



// class vane::gfxapi::WindowRaii: public GfxResource, public gfxapi::Window
// {
// public:
//     WindowRaii(GfxApi&, const char *name, int w, int h);

// protected:
//     SDL_Window   *mSdlWin;
//     SDL_GLContext mSdlGlCtx;
//     SDL_WindowID  mSdlWinID;

//     int32_t mGlVersionMajor;
//     int32_t mGlVersionMinor;

// };


// class vane::gfxapi::Window: public WindowRaii
// {
//     friend class GfxApi;
//     friend class std::shared_ptr<Framebuffer>;
//     friend class std::unique_ptr<Framebuffer>;

//     std::shared_ptr<Framebuffer>   mFramebuffer;
//     std::shared_ptr<ShaderProgram> mQuadProgram;
//     uint32_t mVAO;

// public:
//     Window(GfxApi&, const char *name, int w, int h);
//     virtual ~Window();
//     virtual void onUpdate() final;
//     virtual void onEvent(void*) final;
//     virtual void setFramebufferSrc(const std::shared_ptr<Framebuffer>&) final;
//     void makeCurrent();
// };


// class vane::gfxapi::Framebuffer: public GfxResource, public Framebuffer
// {
//     std::shared_ptr<Texture> mOutTex;
//     void _check_status();

// public:
//     Framebuffer(GfxApi&);
//     virtual ~Framebuffer();

//     void setTarget(const std::shared_ptr<Texture>&);
//     virtual void setTextureDst(const std::shared_ptr<Texture>&) final;

// };


// class vane::gfxapi::Texture: public GfxResource, public Texture
// {
// private:
//     TextureFormat mTextureFormat;

// public:
//     Texture(GfxApi&, int w, int h, const void *data);
//     virtual ~Texture();

//     virtual TextureFormat getTextureFormat() final;
//     virtual void setTextureFormat(TextureFormat) final;

// };


// class vane::gfxapi::GpuProgram: public GfxResource
// {
// public:
//     struct Shader {
//         GpuProgram &mProg;
//         GLuint       mId;
//         bool         mOkay;
//         Shader(GpuProgram &prog, GLuint id, const char *filepath);
//     };

//     GpuProgram(GfxApi &api): GfxResource(api, gl::CreateProgram()) {  }
// };


// class vane::gfxapi::ShaderProgram: public GpuProgram, public ShaderProgram
// {
// public:
//     GpuProgram::Shader mVert, mFrag;
//     ShaderProgram(GfxApi&, const char *v, const char *f);
//     virtual ~ShaderProgram();
// };


// class vane::gfxapi::ComputeProgram: public GpuProgram, public ComputeProgram
// {
// public:
//     GpuProgram::Shader mComp;
//     ComputeProgram(GfxApi&, const char *c);
// };



