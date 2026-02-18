#include "gpu_gl.hpp"


static GLuint create_texture(int w, int h, void *data)
{
    GLuint tex;

    gl::CreateTextures(GL_TEXTURE_2D, 1, &tex);
    
    gl::TextureStorage2D(tex, 1, GL_RGBA8, w, h);
    gl::TextureSubImage2D(tex, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

    gl::TextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::TextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // gl::GenerateTextureMipmap(tex);

    return tex;
}


