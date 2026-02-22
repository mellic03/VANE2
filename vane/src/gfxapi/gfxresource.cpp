#include "vane/gfxapi_gl.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;


GfxResource::GfxResource(GfxApi &api)
:   mApi(api)  {  }


IdType GfxResource::getId()
{
    return mId;
}
