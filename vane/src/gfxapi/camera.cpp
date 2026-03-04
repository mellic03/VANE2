#include "gfxapi/gfxapi_gl.hpp"
#include "gfxapi/camera.hpp"
#include <cstring>

using namespace vane::gfxapi;


Camera::Camera(int w, int h)
:   mFramebuffer( new Framebuffer(Texture(w, h, nullptr, TextureFormat::RGBA_F16)) )
{
    mView = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mProj = glm::perspective(glm::radians(90.0f), 1.0f, 0.001f, 100.0f);
}

