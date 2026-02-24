#pragma once

#include "vane/gfxapi/fwd.hpp"


namespace vane::gfxapi::detail
{
    class Shader
    {
    public:
        uint32_t mId;
        bool     mOkay;
        Shader(vane::gfxapi::ShaderProgram*, uint32_t id, const char *filepath);
    };
}



class vane::gfxapi::ShaderProgram
{
public:
    const IdType mId;
    ShaderProgram();
    ~ShaderProgram();
};


class vane::gfxapi::RenderProgram: public ShaderProgram
{
public:
    detail::Shader mVert, mFrag;
    RenderProgram(const char *vertFilePath, const char *fragFilePath);
};


class vane::gfxapi::ComputeProgram: public ShaderProgram
{
public:
    detail::Shader mComp;
    ComputeProgram(const char *compFilePath);
};



