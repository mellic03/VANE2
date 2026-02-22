#pragma once

#include "vane/gfxapi.hpp"


namespace vane::gfxapi
{
    // template<typename T>
    // struct as_underlying { using type = T; };

    // template<typename T>
    // struct as_underlying<T>::type toUnderlyingType(T);

    // template<typename T>
    // T fromUnderlyingType(as_underlying<T>::type);

    GLenum toUnderlyingType(TextureFormat from);
    TextureFormat fromUnderlyingType(GLenum from);

}

