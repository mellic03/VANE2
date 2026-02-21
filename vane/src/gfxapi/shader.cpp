#include "vane/gl.hpp"
#include "vane/file.hpp"
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


#include <glm/glm.hpp>

// GLuint vaneCreateScreenQuadVAO()
// {
//     struct Vertex
//     {
//         glm::vec3 pos;
//         glm::vec3 nrm;
//         glm::vec2 tex;
//         Vertex() {  };
//         Vertex(int x, int y): pos(float(x), float(y), 0.0f) {  };
//     };

//     /*
//            0        1
//         [-1,-1]  [+1,-1]
//            2        3
//         [-1,+1]  [+1,+1]
//     */

//     static constexpr uint32_t numVtx = 4;
//     static constexpr uint32_t numIdx = 6;

//     Vertex vertices[numVtx] = {
//         Vertex(-1, -1), Vertex(+1, -1),
//         Vertex(-1, +1), Vertex(+1, +1)
//     };

//     uint32_t indices[numIdx] = {
//         0, 1, 2, 1, 3, 2
//     };

//     GLuint vao, vbo, ibo;

//     gl::CreateBuffers(1, &vbo);	
//     gl::NamedBufferStorage(vbo, sizeof(Vertex)*numVtx, vertices, GL_DYNAMIC_STORAGE_BIT);

//     gl::CreateBuffers(1, &ibo);
//     gl::NamedBufferStorage(ibo, sizeof(uint32_t)*numIdx, indices, GL_DYNAMIC_STORAGE_BIT);

//     gl::CreateVertexArrays(1, &vao);

//     gl::VertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
//     gl::VertexArrayElementBuffer(vao, ibo);

//     gl::EnableVertexArrayAttrib(vao, 0);
//     gl::EnableVertexArrayAttrib(vao, 1);
//     gl::EnableVertexArrayAttrib(vao, 2);

//     gl::VertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
//     gl::VertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, nrm));
//     gl::VertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex));

//     gl::VertexArrayAttribBinding(vao, 0, 0);
//     gl::VertexArrayAttribBinding(vao, 1, 0);
//     gl::VertexArrayAttribBinding(vao, 2, 0);
// }




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



static bool check_shader(GLuint shader)
{
    GLint length;
    gl::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if (length > 0)
    {
        char *message = new char[length];
        gl::GetShaderInfoLog(shader, length, &length, message);
        printf("[checkShaderError] %s\n", message);
        delete[] message;
        return true;
    }

    return false;
}


static void compile_shader(GLuint shader_id, const std::string &filepath)
{
    std::string buf = vane::file::loadRaw(filepath);
    const char *src = buf.c_str();

    gl::ShaderSource(shader_id, 1, &src, NULL);
    gl::CompileShader(shader_id);

    GLint result;
    gl::GetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        if (check_shader(shader_id))
        {
            VLOG_ERROR("Failed to compile shader");
        }
    }
}


GLuint vaneCompileScreenQuadProgram()
{
    GLuint prog = gl::CreateProgram();
    GLuint vert = gl::CreateShader(GL_VERTEX_SHADER);
    GLuint frag = gl::CreateShader(GL_FRAGMENT_SHADER);

    compile_shader(vert, "data/shader/quad.vert");
    compile_shader(frag, "data/shader/quad.frag");

    gl::AttachShader(prog, vert);
    gl::AttachShader(prog, frag);
    gl::LinkProgram(prog);
    
    gl::ValidateProgram(prog);
    gl::DeleteShader(vert);
    gl::DeleteShader(frag);

    VLOG_INFO("Compiled screenquad shader");

    return prog;
}


// GLuint vaneCompileScreenQuadProgram()
// {
//     GLuint prog = gl::CreateProgram();
//     GLuint vert = gl::CreateShader(GL_VERTEX_SHADER);
//     GLuint frag = gl::CreateShader(GL_FRAGMENT_SHADER);

//     std::string vstr = vane::file::loadRaw("data/shader/quad.vs");
//     std::string fstr = vane::file::loadRaw("data/shader/quad.fs");
//     const char *vsrc = vstr.c_str();
//     const char *fsrc = fstr.c_str();

//     gl::ShaderSource(vert, 1, &vsrc, NULL);
//     gl::ShaderSource(frag, 1, &fsrc, NULL);

//     gl::CompileShader(vert);
//     gl::CompileShader(frag);

//     gl::AttachShader(prog, vert);
//     gl::AttachShader(prog, frag);
//     gl::LinkProgram(prog);

//     VLOG_INFO("Compiled screenquad shader");

//     return prog;
// }

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

