#pragma once

#include "vane/gfxapi_gl.hpp"


namespace vane::gfxapi
{
    template<typename T>
    struct as_underlying { using type = T; };

    template<typename T>
    struct as_underlying<T>::type toUnderlyingType(const T&);

    template<typename T>
    T fromUnderlyingType(const struct as_underlying<T>::type&);
}

