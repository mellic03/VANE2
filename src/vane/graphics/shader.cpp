#include "gl.hpp"
#include "../util/file.hpp"
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

