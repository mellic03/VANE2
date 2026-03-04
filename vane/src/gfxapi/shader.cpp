#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"
#include "vane/file.hpp"
#include "vane/log.hpp"
#include <fstream>
#include <memory>

using namespace vane::gfxapi;

ShaderProgram::ShaderProgram()
:   mId(gl::CreateProgram()) { }

ShaderProgram::~ShaderProgram()
{ gl::DeleteProgram(mId); }



static vane::FileReader<128*1024> file_reader_;

#include "vane_string.hpp"
void shader_preprocess(const std::string &src) // , std::string &out)
{
    static char incpath[256];

    const char *beg = src.data();
    const char *end = beg + src.length();

    const char *str = beg;
    while (true)
    {
        str = vane::string::seek_ch(str, '#');
        printf("str: 0x%lx\n", (uint64_t)str);
        if (!(*str && str<end))
        {
            return;
        }

        str = vane::string::skip_key(str, "#include");
        VANE_ASSERT(str != nullptr, "Shader preprocess error: expected \"#include\"");

        str = vane::string::skip_ch(str, ' ');
        VANE_ASSERT(
            *str == '\"',
            "Shader preprocess error: expected \"{}\", recieved \"{}\"",
            "\"", *str
        );

        const char *A = str;
        const char *B = vane::string::seek_ch(A+1, '\"');
        VANE_ASSERT(B != nullptr, "Shader preprocess error: expected \"\"\"");

        A += 1; // "filename.glsl" --> filename.glsl"
        B -= 1; //  filename.glsl" --> filename.glsl
        std::memset(incpath, '\0', sizeof(incpath));
        std::strncpy(incpath, A, B-A);
        std::printf("incpath: \"%s\"\n", incpath);
        exit(123);
    }
}


detail::Shader::Shader(ShaderProgram *prog, uint32_t shaderId, const char *filepath)
:   mId(shaderId),
    mOkay(false),
    mFilepath(filepath)
{
    if (!file_reader_.loadFile(filepath))
        return;

    // shader_preprocess(std::string(filepath));
    std::string str = vane::file::loadRaw(std::string(filepath));
    const char *src = str.c_str();

    // gl::ShaderSource(mId, 1, &src, NULL);
    // gl::CompileShader(mId);

    gl::ShaderBinary(1, &mId, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, src, str.length());
    gl::SpecializeShader(mId, "main", 0, 0, 0);

    GLint result, length;
    gl::GetShaderiv(mId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        gl::GetShaderiv(mId, GL_INFO_LOG_LENGTH, &length);
        std::unique_ptr<char> msg(new char[length]);

        assert((length > 0));
    
        gl::GetShaderInfoLog(mId, length, &length, msg.get());
        VLOG_ERROR("[Shader::Shader] {}\n", msg.get());

        mOkay = false;
    }
    else
    {
        gl::AttachShader(prog->mId, mId);
        mOkay = true;
    }
}



RenderProgram::RenderProgram(const char *vertpath, const char *fragpath)
:   mVert(this, gl::CreateShader(GL_VERTEX_SHADER), vertpath),
    mFrag(this, gl::CreateShader(GL_FRAGMENT_SHADER), fragpath)
{
    if (mVert.mOkay && mFrag.mOkay)
    {
        gl::ValidateProgram(mId);
        gl::LinkProgram(mId);
    }
    else
    {
        VLOG_ERROR("Shader compilation failue");
    }

    gl::DeleteShader(mVert.mId);
    gl::DeleteShader(mFrag.mId);

}



ComputeProgram::ComputeProgram(const char *comppath)
:   mComp(this, gl::CreateShader(GL_COMPUTE_SHADER), comppath)
{
    if (mComp.mOkay)
    {
        gl::ValidateProgram(mId);
        gl::LinkProgram(mId);
    }
    else
    {
        VLOG_ERROR("Shader compilation failue");
    }

    gl::DeleteShader(mComp.mId);
}





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


