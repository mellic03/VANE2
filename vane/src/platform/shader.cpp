#include "gl_bindings.hpp"
#include "vane/util/file.hpp"
#include "vane/log.hpp"
#include <fstream>


void rerere()
{
    GLuint prog = gl::CreateProgram();
    GLuint vert = gl::CreateShader(GL_VERTEX_SHADER);
    GLuint frag = gl::CreateShader(GL_FRAGMENT_SHADER);

    std::string vstr = vane::file::loadRaw("vane/shader/quad.vs");
    std::string fstr = vane::file::loadRaw("vane/shader/quad.fs");
    const char *vsrc = vstr.c_str();
    const char *fsrc = fstr.c_str();

    gl::ShaderSource(vert, 1, &vsrc, NULL);
    gl::ShaderSource(frag, 1, &fsrc, NULL);

    gl::CompileShader(vert);
    gl::CompileShader(frag);

    gl::AttachShader(prog, vert);
    gl::AttachShader(prog, frag);
    gl::LinkProgram(prog);

}



static GLuint vaneCreateColorTexture(int width, int height, void *data)
{
    GLuint name;
    gl::CreateTextures(GL_TEXTURE_2D, 1, &name);
    gl::TextureParameteri(name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::TextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl::TextureStorage2D(name, 1, GL_RGBA8, width, height);
    gl::TextureSubImage2D(name, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    return name;
}

static GLuint vaneCreateDepthTexture(int width, int height, void *data)
{
    GLuint name;
    gl::CreateTextures(GL_TEXTURE_2D, 1, &name);
    gl::TextureParameteri(name, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(name, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    gl::TextureParameteri(name, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::TextureParameteri(name, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl::TextureStorage2D(name, 1, GL_DEPTH_COMPONENT24, width, height);
    gl::TextureSubImage2D(name, 0, 0, 0, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, data);
    return name;
}

GLuint vaneCreateFramebuffer()
{
    GLuint colorTex = vaneCreateColorTexture(1024, 1024, nullptr);
    GLuint depthTex = vaneCreateDepthTexture(1024, 1024, nullptr);

    GLuint fbo;
    gl::CreateFramebuffers(1, &fbo);
    gl::NamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, colorTex, 0);
    gl::NamedFramebufferTexture(fbo, GL_DEPTH_ATTACHMENT, depthTex, 0);

    if (gl::CheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        VLOG_ERROR("Error on glCheckNamedFramebufferStatus");
    }

    return fbo;
}


uint32_t compute_shader_init()
{
    std::string filepath = "data/shader/particles.comp";

    GLuint prog = gl::CreateProgram();
    GLuint comp = gl::CreateShader(GL_COMPUTE_SHADER);

    std::string buf = vane::file::loadRaw(filepath);
    const char *csrc = buf.c_str();

    gl::ShaderSource(comp, 1, &csrc, NULL);
    gl::CompileShader(comp);
    gl::AttachShader(prog, comp);
    gl::LinkProgram(prog);

    VLOG_INFO("Compiled compute shader \"{}\"", filepath);

    return (uint32_t)prog;
}


// #include <vane/core/log.hpp>

// void gfx::ShaderArchive::compileSPIRV( const std::string &src, const std::string &dst )
// {
//     syslog log("ShaderArchive::compileSPIRV");

//     auto &conf = vane::GetConfig();
//     std::string glslc = std::string(conf["path"]["binaries"]) + "/glslc";
//     std::string cmd = glslc + " " + src + " -o " + dst;

//     log("glslc: \"%s\"", glslc.c_str());
//     log("cmd: \"%s\"", cmd.c_str());
//     int res = std::system(cmd.c_str());
//     log("res: %d", res);

//     VANE_ASSERT(res==0, "res!=0, res==%d.", res);
// }

