#include "gfxapi/gfxapi_gl.hpp"
#include "gfxapi/buffer.hpp"

using namespace vane::gfxapi;



UboWrapper::UboWrapper(const char *name, size_t size)
:   GfxResource(0),
    mName(name),
    mSize(size),
    mData(std::malloc(size))
{
    gl::CreateBuffers(1, &mId);

    gl::BindBufferBase(GL_UNIFORM_BUFFER, 0, mId);
    gl::NamedBufferData(mId, mSize, nullptr, GL_DYNAMIC_DRAW);
}


UboWrapper::~UboWrapper()
{
    gl::DeleteBuffers(1, &mId);
    std::free(mData);
}


void UboWrapper::bindToProgram(ShaderProgram *P)
{
    GLuint prog = P->mId;
    GLint loc = gl::GetUniformLocation(prog, mName);
    GLint idx = gl::GetUniformBlockIndex(prog, mName);
    // printf("loc, idx: %d, %d\n", loc, idx);
    // gl::UniformBlockBinding(prog, idx, loc);
    gl::BindBufferBase(GL_UNIFORM_BUFFER, idx, mId);
}


void UboWrapper::sendToGpu()
{
    gl::NamedBufferSubData(mId, 0, mSize, mData);
}
